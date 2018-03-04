#include "Core.hh"
#include "meta/conditional_os.hpp"
#include "log/Log.hh"
#include "FileSearcher.hh"
#include "CoreEvent.hh"
#include "EManager.hh"

std::string_view Core::sysLibPath = lel::meta::conditional_os<std::string_view>("lib/S", ".").value;
std::string_view Core::autoLoadedSysRegex = lel::meta::conditional_os<std::string_view>("lib(CLISystem)[.]so", "S[0-9]*[.]dll").value;
lel::Log Core::log{};

Core::Core()
  : _quit{false}
  , _sysLibs{searchLibraries()}
  , _systems{extractSystems(_sysLibs)}
{
}

void Core::run()
{
  EManager::registerListener(shared_from_this());
  while (!shouldQuit())
  {
    for (auto& sys : _systems)
      sys->exec();
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

// static
std::vector<lel::OSLoader> Core::searchLibraries()
{
  ECS::Utility::FileSearcher fs;
  auto libFetcher = [](const auto& path) -> lel::OSLoader
  {
    lel::OSLoader loader;
    loader.loadLibrary(path.c_str());
    log << "Library: " << path << " found\n";
    return loader;
  };

  fs.searchFile(sysLibPath.data(), std::regex(autoLoadedSysRegex.data()));
  return fs.applyOnResult<lel::OSLoader>(libFetcher);
}

std::vector<Core::SysPtr> Core::extractSystems(std::vector<lel::OSLoader>& libs)
{
  std::vector<SysPtr> sys;

  const auto nbLibs = libs.size();
  log << "Number of libraries found: " << nbLibs << "\n";
  for (unsigned i = 0; i < nbLibs; ++i)
  {
    auto& lib = libs[i];
    if (lib.isValid())
    {
      auto ctor = lib.getSymbol<IS*(*)()>("create");
      auto dtor = lib.getSymbol<void(*)(IS*)>("destroy");
      if (!ctor.isValid() || !dtor.isValid())
        {
          log << lib.getLastError() << "\n";
          continue ;
        }
      sys.emplace_back(std::shared_ptr<IS>(ctor(), dtor));
      log << "Library #" << i << " has a valid system\n";
    }
    else
      {
        log << "Library #" << i << " has NOT a valid system\n";
        log << lib.getLastError() << "\n";
      }
  }
  log << "Valid systems found: " << sys.size() << "\n";
  return sys;
}
