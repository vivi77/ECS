#include "Core.hh"
#include "meta/conditional_os.hpp"
#include "E/CoreEvent/CoreEvent.hh"
#include "E/EManager/EManager.hh"
#include "StartupLoader.hh"
#include "S/CoreProxy/CoreProxy.hh"
#include "S/IS.hh"
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

  void updateRemoveRequest(std::list<std::string>& removeRequest, std::list<lel::ecs::CoreSystemData>& datalist)
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
        lel::ecs::event::EManager::fire<lel::ecs::event::CoreEvent>(lel::ecs::event::CoreEvent::Type::SYSTEM_NOT_FOUND, systemPath);
        continue;
      }

      if (it->sys->isListener())
        lel::ecs::event::EManager::deregisterListener(castToListener(it->sys));
      it->sys->atRemove();
      lel::ecs::event::EManager::fire<lel::ecs::event::CoreEvent>(lel::ecs::event::CoreEvent::Type::REM_SYSTEM_SUCCESS,
                                                                  it->path.u8string(),
                                                                  to_string(it->sys.get()),
                                                                  std::to_string(it->sys->getID()));
      datalist.erase(it);
    }
    removeRequest.clear();
  }

  void reverseClear(std::list<lel::ecs::CoreSystemData>& container)
  {
    while (!container.empty())
    {
      if (container.back().sys->isListener())
        lel::ecs::event::EManager::deregisterListener(castToListener(container.back().sys));
      container.back().sys->atRemove();
      lel::ecs::event::EManager::fire<lel::ecs::event::CoreEvent>(lel::ecs::event::CoreEvent::Type::REM_SYSTEM_SUCCESS,
                                                                  container.back().path.u8string(),
                                                                  to_string(container.back().sys.get()),
                                                                  std::to_string(container.back().sys->getID()));
      container.pop_back();
    }
  }
} /* ! */

namespace lel::ecs
{
  std::string_view Core::sysLibPath = lel::meta::conditional_os<std::string_view>("lib/S/", "./").value;
  std::string_view Core::autoLoadedSysRegex = lel::meta::conditional_os<std::string_view>("lib(CLISystem)[.]so", "S[0-9]*[.]dll").value;

  Core::Core()
  {
    // MUST be setted before the loading of any library
    //CoreProxy::setSystemsList(_data);
    //CoreProxy::setEntityManager(_entityManager);
    _data = setupData();
  }

  void Core::run()
  {
    if (_data.empty())
    {
      event::EManager::fire<event::CoreEvent>(event::CoreEvent::Type::CLOSING);
      return ;
    }

    event::EManager::registerListener(shared_from_this());
    while (!shouldQuit() && !_data.empty())
    {
      for (auto& data : _data)
      {
        data.sys->exec();
      }
      delayedEventUpdate();
    }
    event::EManager::deregisterListener(shared_from_this());
    event::EManager::fire<event::CoreEvent>(event::CoreEvent::Type::CLOSING);
    reverseClear(_data);
  }

  void Core::update(const IEListener::EPtr& e)
  {
    if (e->getID() == event::CoreEvent::getEventID())
    {
      const auto event = std::static_pointer_cast<event::CoreEvent>(e);
      switch (event->getType())
      {
        case event::CoreEvent::Type::EXIT:
          stopCore();
          break;
        case event::CoreEvent::Type::ADD_SYSTEM:
          _addRequest.emplace_back(event->getData()[0]);
          break;
        case event::CoreEvent::Type::REM_SYSTEM:
          _remRequest.emplace_back(event->getData()[0]);
          break;
        default:
          break;
      }
    }
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
    using CoreEvent = lel::ecs::event::CoreEvent;
    using EManager = lel::ecs::event::EManager;

    if (!data.loader.isValid())
    {
      EManager::fire<CoreEvent>(CoreEvent::Type::SYSTEM_NOT_FOUND,
                                data.path.u8string(),
                                data.loader.getLastError());
      std::cerr << data.loader.getLastError() << "\n";
      return false;
    }

    auto ctor = data.loader.getSymbol<lel::ecs::system::IS*(*)()>("create");
    auto dtor = data.loader.getSymbol<void(*)(lel::ecs::system::IS*)>("destroy");
    if (!ctor.isValid() || !dtor.isValid())
    {
      EManager::fire<CoreEvent>(CoreEvent::Type::INVALID_SYSTEM,
                                data.path.filename().u8string(),
                                data.loader.getLastError());
      return false;
    }

    data.sys = std::shared_ptr<lel::ecs::system::IS>(ctor(), dtor);
    data.sys->setup();
    if (data.sys->isListener())
      EManager::registerListener(castToListener(data.sys));
    _entityManager.updateSysComponent(data.sys);
    return true;
  }

  std::list<lel::ecs::CoreSystemData> Core::setupData()
  {
    using EManager = lel::ecs::event::EManager;
    using CoreEvent = lel::ecs::event::CoreEvent;

    std::list<lel::ecs::CoreSystemData> l;
    lel::ecs::StartupLoader startup{"startup.ecs"};

    auto libFetcher = [this, &l](const std::experimental::filesystem::path& path)
    {
      lel::ecs::CoreSystemData data;
      data.path = lel::ecs::Core::sysLibPath;
      data.path += path;
      data.loader.loadLibrary(data.path.u8string().c_str());
      if (trySystemRegistering(data))
      {
        l.emplace_back(data);
        EManager::fire<CoreEvent>(CoreEvent::Type::ADD_SYSTEM_SUCCESS,
                                  data.path.u8string(),
                                  to_string(data.sys.get()),
                                  std::to_string(data.sys->getID()));
      }
    };
    startup.applyOnPaths(libFetcher);
    return l;
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
        lel::ecs::event::EManager::fire<lel::ecs::event::CoreEvent>(lel::ecs::event::CoreEvent::Type::ALREADY_ADDED_SYSTEM,
                                                                    data.path.u8string());
        continue ;
      }

      data.loader.loadLibrary(data.path.u8string().c_str());
      if (trySystemRegistering(data))
      {
        datalist.emplace_back(std::move(data));
        lel::ecs::event::EManager::fire<lel::ecs::event::CoreEvent>(lel::ecs::event::CoreEvent::Type::ADD_SYSTEM_SUCCESS,
                                                                    datalist.back().path.u8string(),
                                                                    to_string(datalist.back().sys.get()),
                                                                    std::to_string(datalist.back().sys->getID()));
      }
    }
    addRequest.clear();
  }
} /* !lel::ecs */
