#include "CoreSystemProxy.hh"

CoreSystemProxy::SystemContainer* CoreSystemProxy::_systems;

void CoreSystemProxy::setSystemsList(SystemContainer& systems)
{
  static bool accessed = false;
  if (!accessed)
  {
    _systems = &systems;
    accessed = true;
  }
}

void CoreSystemProxy::registerEntityInSystems(const std::shared_ptr<Entity>& entity)
{
  if (!_systems)
    return ;

  for (auto& sys : *_systems)
    sys->registerEntity(entity);
}
