#include "Core.hh"
#include "meta/conditional_os.hpp"
//#include "E/CoreEvent/CoreEvent.hh"
#include "E/EManager/EManager.hh"
#include "StartupLoader.hh"
#include "S/CoreProxy/CoreProxy.hh"
#include "S/IS.hh"
#include "S/IDSystem.hh"
#include <iostream>
#include <algorithm>
#include <sstream>

namespace
{
  std::string to_string(void *ptr)
  {
    std::stringstream ss;
    ss << ptr;
    return ss.str();
  }

  // TODO: Find a better way to check than this
  std::shared_ptr<lel::ecs::event::IEListener> castToListener(const std::shared_ptr<lel::ecs::system::IS>& sys)
  {
    return std::dynamic_pointer_cast<lel::ecs::event::IEListener>(sys);
  }
} /* ! */

namespace lel::ecs
{
  std::string_view Core::sysLibPath = lel::meta::conditional_os<std::string_view>("lib/S/", "./").value;
  std::string_view Core::autoLoadedSysRegex = lel::meta::conditional_os<std::string_view>("lib(CLISystem)[.]so", "S[0-9]*[.]dll").value;

  Core::Core()
  {
    setupData();
  }

  void Core::run()
  {
    if (_data.empty())
    {
      //_eventManager.fire<event::CoreEvent>(event::CoreEvent::Type::CLOSING);
      return ;
    }

    _eventManager.registerListener(shared_from_this());
    while (!shouldQuit() && !_data.empty())
    {
      for (auto& data : _data)
      {
        data.sys->exec();
      }
      delayedEventUpdate();
    }
    _eventManager.deregisterListener(shared_from_this());
    //_eventManager.fire<event::CoreEvent>(event::CoreEvent::Type::CLOSING);
    reverseClear(_data);
  }

  void Core::update(const IEListener::EPtr& e)
  {
    //if (e->getID() == event::CoreEvent::getEventID())
    //{
      //const auto event = std::static_pointer_cast<event::CoreEvent>(e);
      //switch (event->getType())
      //{
        //case event::CoreEvent::Type::EXIT:
          //stopCore();
          //break;
        //case event::CoreEvent::Type::ADD_SYSTEM:
          //_addRequest.emplace_back(event->getData()[0]);
          //break;
        //case event::CoreEvent::Type::REM_SYSTEM:
          //_remRequest.emplace_back(event->getData()[0]);
          //break;
        //default:
          //break;
      //}
    //}
  }

  bool Core::shouldQuit() const
  {
    return _quit;
  }

  void Core::stopCore()
  {
    _quit = true;
  }

  void Core::delayedEventUpdate()
  {
    updateAddRequest(_addRequest, _data);
    updateRemoveRequest(_remRequest, _data);
  }

  bool Core::trySystemRegistering(lel::ecs::CoreSystemData& data)
  {
    //using CoreEvent = lel::ecs::event::CoreEvent;

    if (!data.loader.isValid())
    {
      //_eventManager.fire<CoreEvent>(CoreEvent::Type::SYSTEM_NOT_FOUND,
                                    //data.path.u8string(),
                                    //data.loader.getLastError());
      std::cerr << data.loader.getLastError() << "\n";
      return false;
    }

    auto ctor = data.loader.getSymbol<lel::ecs::system::IS*(*)(CoreProxy*)>("create");
    auto dtor = data.loader.getSymbol<void(*)(lel::ecs::system::IS*)>("destroy");
    if (!ctor.isValid() || !dtor.isValid())
    {
      //_eventManager.fire<CoreEvent>(CoreEvent::Type::INVALID_SYSTEM,
                                    //data.path.filename().u8string(),
                                    //data.loader.getLastError());
      return false;
    }

    auto proxy = new CoreProxy{_data, _entityManager, _eventManager};
    data.sys = std::shared_ptr<lel::ecs::system::IS>(ctor(proxy), dtor);
    data.sys->setup();
    if (data.sys->isListener())
      _eventManager.registerListener(castToListener(data.sys));
    _entityManager.tryRegisterEntitiesInSystem(data.sys);
    return true;
  }

  void Core::setupData()
  {
    //using CoreEvent = lel::ecs::event::CoreEvent;

    lel::ecs::StartupLoader startup{"startup.ecs"};

    auto libFetcher = [this](const std::experimental::filesystem::path& path)
    {
      lel::ecs::CoreSystemData data;
      data.path = lel::ecs::Core::sysLibPath;
      data.path += path;
      data.loader.loadLibrary(data.path.u8string().c_str());
      if (trySystemRegistering(data))
      {
        _data.emplace_back(data);
        //_eventManager.fire<CoreEvent>(CoreEvent::Type::ADD_SYSTEM_SUCCESS,
                                      //data.path.u8string(),
                                      //to_string(data.sys.get()),
                                      //std::to_string(data.sys->getID()));
      }
    };
    startup.applyOnPaths(libFetcher);
  }

  void Core::updateAddRequest(std::list<std::string>& addRequest, std::list<lel::ecs::CoreSystemData>& datalist)
  {
    for (const auto& addSysPath : addRequest)
    {
      lel::ecs::CoreSystemData data;
      data.path = lel::ecs::Core::sysLibPath;
      data.path += addSysPath;

      if (lel::OSDLLoader::isLibraryLoaded(addSysPath.c_str()))
      {
        //_eventManager.fire<lel::ecs::event::CoreEvent>(lel::ecs::event::CoreEvent::Type::ALREADY_ADDED_SYSTEM,
                                                       //data.path.u8string());
        continue ;
      }

      data.loader.loadLibrary(data.path.u8string().c_str());
      if (trySystemRegistering(data))
      {
        datalist.emplace_back(std::move(data));
        //_eventManager.fire<lel::ecs::event::CoreEvent>(lel::ecs::event::CoreEvent::Type::ADD_SYSTEM_SUCCESS,
                                                       //datalist.back().path.u8string(),
                                                       //to_string(datalist.back().sys.get()),
                                                       //std::to_string(datalist.back().sys->getID()));
      }
    }
    addRequest.clear();
  }

  void Core::updateRemoveRequest(std::list<std::string>& removeRequest, std::list<lel::ecs::CoreSystemData>& datalist)
  {
    for (const auto& removeSysPath : removeRequest)
    {
      auto systemPath = removeSysPath;

      auto beginIt = std::begin(datalist);
      auto endIt = std::end(datalist);
      auto pred = [&systemPath](const lel::ecs::CoreSystemData& data) -> bool
      {
        return data.path.filename() == systemPath;
      };
      auto it = std::find_if(beginIt, endIt, pred);

      if (it == endIt)
      {
        //_eventManager.fire<event::CoreEvent>(event::CoreEvent::Type::SYSTEM_NOT_FOUND, systemPath);
        continue;
      }

      if (it->sys->isListener())
        _eventManager.deregisterListener(castToListener(it->sys));
      it->sys->atRemove();
      //_eventManager.fire<event::CoreEvent>(event::CoreEvent::Type::REM_SYSTEM_SUCCESS,
                                           //it->path.u8string(),
                                           //to_string(it->sys.get()),
                                           //std::to_string(it->sys->getID()));
      datalist.erase(it);
    }
    removeRequest.clear();
  }

  void Core::reverseClear(std::list<CoreSystemData>& container)
  {
    while (!container.empty())
    {
      if (container.back().sys->isListener())
        _eventManager.deregisterListener(castToListener(container.back().sys));
      container.back().sys->atRemove();
      //_eventManager.fire<lel::ecs::event::CoreEvent>(lel::ecs::event::CoreEvent::Type::REM_SYSTEM_SUCCESS,
                                                     //container.back().path.u8string(),
                                                     //to_string(container.back().sys.get()),
                                                     //std::to_string(container.back().sys->getID()));
      container.pop_back();
    }
  }
} /* !lel::ecs */
