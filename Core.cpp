#include "Core.hh"
#include "meta/conditional_os.hpp"
#include "log/Log.hh"
#include "FileSearcher.hh"
#include "CoreEvent.hh"
#include "EManager.hh"

namespace
{
  bool checkSystemValidity(SystemData& data)
  {
    if (!data.loader.isValid())
    {
      Core::log << "Library '" << data.path.filename().u8string() << "' has an invalid system\n";
      return false;
    }

    auto ctor = data.loader.getSymbol<IS*(*)()>("create");
    auto dtor = data.loader.getSymbol<void(*)(IS*)>("destroy");
    if (!ctor.isValid() || !dtor.isValid())
    {
      Core::log << data.loader.getLastError() << "\n";
      return false;
    }

    data.sys = std::shared_ptr<IS>(ctor(), dtor);
    Core::log << "Library '" << data.path.filename().u8string()
      << "' has a valid system\n";
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
      Core::log << "Library: " << data.path.filename().u8string() << " found\n";
      if (checkSystemValidity(data))
      {
        l.emplace_back(std::move(data));
        Core::log << "System '" << l.back().path.filename().u8string() << "' added\n";
      }
    };

    (void)fs.applyOnResult(libFetcher);
    return l;
  }
} /* ! */

std::string_view Core::sysLibPath = lel::meta::conditional_os<std::string_view>("lib/S/", ".").value;
std::string_view Core::autoLoadedSysRegex = lel::meta::conditional_os<std::string_view>("lib(CLISystem)[.]so", "S[0-9]*[.]dll").value;
lel::Log Core::log{};

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
    log << "There is no valid system\nQuitting program\n";
    return ;
  }

  EManager::registerListener(shared_from_this());
  while (!shouldQuit() && !_data.empty())
  {
    for (auto& data : _data)
      data.sys->exec();
    delayedEventUpdate();
  }
  if (_data.empty())
    log << "There is no more system\nExiting program\n";
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
      log << "Stop core requested\n";
      stopCore();
      break;
    case CoreEvent::Type::ADD_SYSTEM:
      _addRequest.emplace_back(event->getData());
      break;
    case CoreEvent::Type::REM_SYSTEM:
      _remRequest.emplace_back(event->getData());
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
  for (const auto& addSysPath : _addRequest)
  {
    SystemData data;
    data.path = static_cast<std::string>(sysLibPath) + addSysPath;
    log << "Add system '" << data.path << "' requested\n";

    auto beginIt = std::begin(_data);
    auto endIt = std::end(_data);
    auto pred = [&data](const SystemData& it) -> bool
    {
      return data.path == it.path;
    };
    auto it = std::find_if(beginIt, endIt, pred);
    if (it != endIt)
    {
      log << "System '" << data.path << "' already added\n";
      continue ;
    }

    data.loader.loadLibrary(data.path.u8string().c_str());
    if (checkSystemValidity(data))
    {
      _data.emplace_back(std::move(data));
      log << "System '" << data.path.filename().u8string() << "' added\n";
    }
  }
  _addRequest.clear();

  for (const auto& remSysPath : _remRequest)
  {
    auto systemPath = remSysPath;
    log << "Remove system '" << systemPath << "' requested\n";

    auto beginIt = std::begin(_data);
    auto endIt = std::end(_data);
    auto pred = [&systemPath](const SystemData& data) -> bool
    {
      return data.path.filename() == systemPath;
    };
    auto it = std::find_if(beginIt, endIt, pred);
    if (it != endIt)
    {
      log << "Removing system with path:'" << it->path << "'\n";
      _data.erase(it);
    }
    else
      log << "System not found\n";
  }
  _remRequest.clear();
}
