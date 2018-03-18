#include "Core.hh"
#include "meta/conditional_os.hpp"
#include "FileSearcher.hh"
#include "CoreEvent.hh"
#include "EManager.hh"

namespace
{
  bool checkSystemValidity(SystemData& data)
  {
    if (!data.loader.isValid())
    {
      EManager::fire<CoreEvent>(CoreEvent::Type::SYSTEM_NOT_FOUND,
                                data.path.u8string(),
                                data.loader.getLastError());
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
    if (data.sys->isListener())
      EManager::registerListenerSystem(data.sys);
    return true;
  }

  std::list<SystemData> setupData()
  {
    std::list<SystemData> l;

    ECS::Utility::FileSearcher fs;
    fs.searchFile(Core::sysLibPath.data(), std::regex(Core::autoLoadedSysRegex.data()));
    auto libFetcher = [&l](const std::experimental::filesystem::path& path)
    {
      SystemData data;
      data.path = path;
      data.loader.loadLibrary(data.path.u8string().c_str());
      if (checkSystemValidity(data))
      {
        l.emplace_back(std::move(data));
        EManager::fire<CoreEvent>(CoreEvent::Type::ADD_SYSTEM_SUCCESS,
                                  l.back().path.u8string());
      }
    };

    (void)fs.applyOnResult(libFetcher);
    return l;
  }

  void updateAddRequest(std::list<std::string>& addRequest, std::list<SystemData>& datalist)
  {
    for (const auto& addSysPath : addRequest)
    {
      SystemData data;
      data.path = static_cast<std::string>(Core::sysLibPath) + addSysPath;

      if (lel::OSLoader::isLibraryLoaded(addSysPath.c_str()))
      {
        EManager::fire<CoreEvent>(CoreEvent::Type::ALREADY_ADDED_SYSTEM,
                                  data.path.u8string());
        continue ;
      }

      data.loader.loadLibrary(data.path.u8string().c_str());
      if (checkSystemValidity(data))
      {
        datalist.emplace_back(std::move(data));
        EManager::fire<CoreEvent>(CoreEvent::Type::ADD_SYSTEM_SUCCESS,
                                  datalist.back().path.u8string());
      }
    }
    addRequest.clear();
  }

  void updateRemoveRequest(std::list<std::string>& removeRequest, std::list<SystemData>& datalist)
  {
    for (const auto& removeSysPath : removeRequest)
    {
      auto systemPath = removeSysPath;

      auto beginIt = std::begin(datalist);
      auto endIt = std::end(datalist);
      auto pred = [&systemPath](const SystemData& data) -> bool
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
                                it->path.u8string());
      datalist.erase(it);
    }
    removeRequest.clear();
  }
} /* ! */

std::string_view Core::sysLibPath = lel::meta::conditional_os<std::string_view>("lib/S/", ".").value;
std::string_view Core::autoLoadedSysRegex = lel::meta::conditional_os<std::string_view>("lib(CLISystem)[.]so", "S[0-9]*[.]dll").value;

Core::Core()
  : _quit{false}
  , _data{setupData()}
  , _addRequest{}
  , _remRequest{}
{}

void Core::run()
{
  if (_data.empty())
  {
    EManager::fire<CoreEvent>(CoreEvent::Type::CLOSING);
    return ;
  }

  EManager::registerListener(shared_from_this());
  while (!shouldQuit() && !_data.empty())
  {
    for (auto& data : _data)
      data.sys->exec();
    delayedEventUpdate();
  }
  EManager::fire<CoreEvent>(CoreEvent::Type::CLOSING);
  EManager::deregisterListener(shared_from_this());
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
