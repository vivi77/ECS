#include "Core.hh"
#include "StartupLoader.hh"
#include "meta/conditional_os.hpp"
#include "CoreEvent.hh"
#include "IS.hh"
#include "IDSystem.hh"
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
    using CoreEvent = event::CoreEvent;

    if (_data.empty())
    {
      _eventManager.fire<CoreEvent>(CoreEvent::Type::CLOSING);
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
    _eventManager.fire<CoreEvent>(CoreEvent::Type::CLOSING);
    reverseClear(_data);
  }

  void Core::update(const IEListener::EPtr&)
  {
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
    updateAddRequest();
    updateRemoveRequest();
    updateReloadRequest();
  }

  bool Core::trySystemRegistering(CoreSystemData& data)
  {
    using CoreEvent = event::CoreEvent;

    if (!data.loader.isValid())
    {
      _eventManager.fire<CoreEvent>(CoreEvent::Type::SYSTEM_NOT_FOUND,
                                    data.path.u8string(),
                                    data.loader.getLastError());
      std::cerr << data.loader.getLastError() << "\n";
      return false;
    }

    auto ctor = data.loader.getSymbol<system::IS*(*)(CoreProxy&)>("create");
    auto dtor = data.loader.getSymbol<void(*)(system::IS*)>("destroy");
    if (!ctor.isValid() || !dtor.isValid())
    {
      _eventManager.fire<CoreEvent>(CoreEvent::Type::INVALID_SYSTEM,
                                    data.path.filename().u8string(),
                                    data.loader.getLastError());
      return false;
    }

    _proxies.emplace_back(_data, _entityManager, _eventManager, _quit);
    data.sys = std::shared_ptr<system::IS>(ctor(_proxies.back()), dtor);
    data.sys->setup();
    if (data.sys->isListener())
      _eventManager.registerListener(castToListener(data.sys));
    _entityManager.tryRegisterEntitiesInSystem(data.sys);
    return true;
  }

  void Core::setupData()
  {
    using CoreEvent = event::CoreEvent;

    StartupLoader startup{"startup.ecs"};

    auto libFetcher = [this](const std::experimental::filesystem::path& path)
    {
      CoreSystemData data;
      data.path = Core::sysLibPath;
      data.path += path;
      data.loader.loadLibrary(data.path.u8string().c_str());
      if (trySystemRegistering(data))
      {
        _data.emplace_back(data);
        _eventManager.fire<CoreEvent>(CoreEvent::Type::ADD_SYSTEM_SUCCESS,
                                      data.path.u8string(),
                                      to_string(data.sys.get()),
                                      std::to_string(data.sys->getID()));
      }
    };
    startup.applyOnPaths(libFetcher);
  }

  void Core::updateAddRequest()
  {
    for (auto& proxy : _proxies)
    {
      for (const auto& sysPath : proxy._systemsToAdd)
        addSystem(sysPath);
      proxy._systemsToAdd.clear();
    }
  }

  void Core::updateRemoveRequest()
  {
    for (auto& proxy : _proxies)
    {
      for (const auto& sysPath : proxy._systemsToRemove)
        removeSystem(sysPath);
      proxy._systemsToRemove.clear();
    }
  }

  void Core::updateReloadRequest()
  {
    for (auto& proxy : _proxies)
    {
      for (const auto& sysPath : proxy._systemsToReload)
      {
        removeSystem(sysPath);
        addSystem(sysPath);
      }
      proxy._systemsToReload.clear();
    }
  }

  void Core::reverseClear(std::list<CoreSystemData>& container)
  {
    using CoreEvent = event::CoreEvent;

    while (!container.empty())
    {
      auto& backData = container.back();
      if (backData.sys->isListener())
        _eventManager.deregisterListener(castToListener(backData.sys));
      backData.sys->atRemove();
      _eventManager.fire<CoreEvent>(CoreEvent::Type::REM_SYSTEM_SUCCESS,
                                    backData.path.u8string(),
                                    to_string(backData.sys.get()),
                                    std::to_string(backData.sys->getID()));
      container.pop_back();
    }
  }

  void Core::addSystem(const std::string& sysPath)
  {
    CoreSystemData data;
    data.path = Core::sysLibPath;
    data.path += sysPath;

    if (OSDLLoader::isLibraryLoaded(sysPath.c_str()))
    {
      _eventManager.fire<event::CoreEvent>(event::CoreEvent::Type::ALREADY_ADDED_SYSTEM,
                                           data.path.u8string());
      return ;
    }

    data.loader.loadLibrary(data.path.u8string().c_str());
    if (trySystemRegistering(data))
    {
      _data.emplace_back(std::move(data));
      _eventManager.fire<event::CoreEvent>(event::CoreEvent::Type::ADD_SYSTEM_SUCCESS,
                                           _data.back().path.u8string(),
                                           to_string(_data.back().sys.get()),
                                           std::to_string(_data.back().sys->getID()));
    }
  }

  void Core::removeSystem(const std::string& sysPath)
  {
    const auto endIt = std::end(_data);
    const auto pred = [&sysPath](const CoreSystemData& data) -> bool
    {
      return data.path.filename() == sysPath;
    };
    const auto it = std::find_if(std::begin(_data), endIt, pred);
    if (it == endIt)
    {
      _eventManager.fire<event::CoreEvent>(event::CoreEvent::Type::SYSTEM_NOT_FOUND, sysPath);
      return ;
    }

    if (it->sys->isListener())
      _eventManager.deregisterListener(castToListener(it->sys));
    it->sys->atRemove();
    _eventManager.fire<event::CoreEvent>(event::CoreEvent::Type::REM_SYSTEM_SUCCESS,
                                         it->path.u8string(),
                                         to_string(it->sys.get()),
                                         std::to_string(it->sys->getID()));
    _data.erase(it);
  }
} /* !lel::ecs */
