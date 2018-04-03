#include "CoreSystemProxy.hh"

namespace lel::ecs
{
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

  void CoreSystemProxy::registerEntityInSystems(const std::shared_ptr<entity::Entity>& entity)
  {
    if (!_systems)
      return ;

    for (auto& data : *_systems)
      data.sys->registerEntity(entity);
  }
} /* !lel::ecs */
