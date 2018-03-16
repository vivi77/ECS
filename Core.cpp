#include "Core.hh"
#include "meta/conditional_os.hpp"
#include "log/Log.hh"
#include "FileSearcher.hh"
#include "CoreEvent.hh"
#include "EManager.hh"

namespace
{
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

      if (!data.loader.isValid())
      {
        Core::log << "Library '" << data.path.filename().u8string() << "' has an invalid system\n";
        return ;
      }

      auto ctor = data.loader.getSymbol<IS*(*)()>("create");
      auto dtor = data.loader.getSymbol<void(*)(IS*)>("destroy");
      if (!ctor.isValid() || !dtor.isValid())
      {
        Core::log << data.loader.getLastError() << "\n";
        return ;
      }

      data.sys = std::shared_ptr<IS>(ctor(), dtor);
      Core::log << "Library '" << data.path.filename().u8string() << "' has a valid system\n";
      l.emplace_back(std::move(data));
    };

    (void)fs.applyOnResult(libFetcher);
    return l;
  }
} /* ! */

std::string_view Core::sysLibPath = lel::meta::conditional_os<std::string_view>("lib/S", ".").value;
std::string_view Core::autoLoadedSysRegex = lel::meta::conditional_os<std::string_view>("lib(CLISystem)[.]so", "S[0-9]*[.]dll").value;
lel::Log Core::log{};

Core::Core()
  : _quit{false}
  , _data{setupData()}
{}

void Core::run()
{
  if (_data.empty())
  {
    log << "There is no valid system\nQuitting program\n";
    return ;
  }

  EManager::registerListener(shared_from_this());
  while (!shouldQuit())
  {
    for (auto& data : _data)
      data.sys->exec();
  }
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
      {
        auto systemName = event->getData();
        log << "Add system '" << systemName << "' requested\n";
      }
      break;
    case CoreEvent::Type::REM_SYSTEM:
      {
        auto systemName = event->getData();
        log << "Remove system '" << systemName << "' requested\n";
      }
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
