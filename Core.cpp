#include "Core.hh"
#include "meta/conditional_os.hpp"
#include "CoreEvent.hh"
#include "EManager.hh"
#include "CManager.hh"
#include "Entity/EntityManager.hh"
#include "StartupLoader.hh"
#include "S/CoreSystemProxy/CoreSystemProxy.hh"
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

  bool trySystemRegistering(CoreSystemData& data)
  {
    if (!data.loader.isValid())
    {
      EManager::fire<CoreEvent>(CoreEvent::Type::SYSTEM_NOT_FOUND,
                                data.path.u8string(),
                                data.loader.getLastError());
      std::cerr << data.loader.getLastError() << "\n";
      return false;
    }

    auto ctor = data.loader.getSymbol<IS*(*)()>("create");
    auto dtor = data.loader.getSymbol<void(*)(IS*)>("destroy");
    if (!ctor.isValid() || !dtor.isValid())
    {
      EManager::fire<CoreEvent>(CoreEvent::Type::INVALID_SYSTEM,
                                data.path.filename().u8string(),
                                data.loader.getLastError());
      return false;
    }

    data.sys = std::shared_ptr<IS>(ctor(), dtor);
    data.sys->setup();
    if (data.sys->isListener())
      EManager::registerListenerSystem(data.sys);
    EntityManager::updateSysComponent(data.sys);
    return true;
  }

  std::list<CoreSystemData> setupData()
  {
    std::list<CoreSystemData> l;
    StartupLoader startup{"startup.ecs"};

    auto libFetcher = [&l](const std::experimental::filesystem::path& path)
    {
      CoreSystemData data;
      data.path = Core::sysLibPath;
      data.path += path;
      data.loader.loadLibrary(data.path.u8string().c_str());
      if (trySystemRegistering(data))
      {
        l.emplace_back(data);
        EManager::fire<CoreEvent>(CoreEvent::Type::ADD_SYSTEM_SUCCESS,
                                  data.path.u8string(), to_string(data.sys.get()));
      }
    };
    startup.applyOnPaths(libFetcher);
    return l;
  }

  void updateAddRequest(std::list<std::string>& addRequest, std::list<CoreSystemData>& datalist)
  {
    for (const auto& addSysPath : addRequest)
    {
      CoreSystemData data;
      data.path = Core::sysLibPath;
      data.path += addSysPath;

      if (lel::OSDLLoader::isLibraryLoaded(addSysPath.c_str()))
      {
        EManager::fire<CoreEvent>(CoreEvent::Type::ALREADY_ADDED_SYSTEM,
                                  data.path.u8string());
        continue ;
      }

      data.loader.loadLibrary(data.path.u8string().c_str());
      if (trySystemRegistering(data))
      {
        datalist.emplace_back(std::move(data));
        EManager::fire<CoreEvent>(CoreEvent::Type::ADD_SYSTEM_SUCCESS,
                                  datalist.back().path.u8string(), to_string(datalist.back().sys.get()));
      }
    }
    addRequest.clear();
  }

  void updateRemoveRequest(std::list<std::string>& removeRequest, std::list<CoreSystemData>& datalist)
  {
    for (const auto& removeSysPath : removeRequest)
    {
      auto systemPath = removeSysPath;

      auto beginIt = std::begin(datalist);
      auto endIt = std::end(datalist);
      auto pred = [&systemPath](const CoreSystemData& data) -> bool
      {
        return data.path.filename() == systemPath;
      };
      auto it = std::find_if(beginIt, endIt, pred);

      if (it == endIt)
      {
        EManager::fire<CoreEvent>(CoreEvent::Type::SYSTEM_NOT_FOUND, systemPath);
        continue;
      }

      if (it->sys->isListener())
        EManager::deregisterListenerSystem(it->sys);
      EManager::fire<CoreEvent>(CoreEvent::Type::REM_SYSTEM_SUCCESS,
                                it->path.u8string(), to_string(it->sys.get()));
      it->sys->atRemove();
      datalist.erase(it);
    }
    removeRequest.clear();
  }

  void reverseClear(std::list<CoreSystemData>& container)
  {
    while (!container.empty())
    {
      if (container.back().sys->isListener())
        EManager::deregisterListenerSystem(container.back().sys);
      EManager::fire<CoreEvent>(CoreEvent::Type::REM_SYSTEM_SUCCESS,
                                container.back().path.u8string(), to_string(container.back().sys.get()));
      container.back().sys->atRemove();
      container.pop_back();
    }
  }
} /* ! */

std::string_view Core::sysLibPath = lel::meta::conditional_os<std::string_view>("lib/S/", "./").value;
std::string_view Core::autoLoadedSysRegex = lel::meta::conditional_os<std::string_view>("lib(CLISystem)[.]so", "S[0-9]*[.]dll").value;

Core::Core()
  : _data{setupData()}
{}

void Core::run()
{
  if (_data.empty())
  {
    EManager::fire<CoreEvent>(CoreEvent::Type::CLOSING);
    return ;
  }

  CoreSystemProxy::setSystemsList(_data);
  EManager::registerListener(shared_from_this());
  while (!shouldQuit() && !_data.empty())
  {
    for (auto& data : _data)
    {
      data.sys->exec();
    }
    delayedEventUpdate();
  }
  EManager::deregisterListener(shared_from_this());
  reverseClear(_data);
  EManager::fire<CoreEvent>(CoreEvent::Type::CLOSING);
}

void Core::update(const IEListener::EPtr& e)
{
  if (e->getID() == CoreEvent::getEventID())
  {
    const auto event = std::static_pointer_cast<CoreEvent>(e);
    switch (event->getType())
    {
    case CoreEvent::Type::EXIT:
      stopCore();
      break;
    case CoreEvent::Type::ADD_SYSTEM:
      _addRequest.emplace_back(event->getData()[0]);
      break;
    case CoreEvent::Type::REM_SYSTEM:
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
