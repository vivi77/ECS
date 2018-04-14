#include "CoreProxy.hh"
#include "S/IS.hh"

namespace lel::ecs
{
  CoreProxy::CoreProxy(SystemContainer* systems, entity::EntityManager* manager)
    : _systems{systems}
    , _entityManager{manager}
  {
  }

  entity::EntityManager::EntityPtr CoreProxy::createEntity(std::initializer_list<entity::EntityManager::ComponentPtr> il)
  {
    if (!_entityManager)
      return nullptr;

    auto entity = _entityManager->createEntity(il);
    registerEntityInSystems(entity);
    return entity;
  }

  void CoreProxy::registerEntityInSystems(const std::shared_ptr<entity::Entity>& entity)
  {
    if (!_systems)
      return ;

    for (auto& data : *_systems)
      data.sys->registerEntity(entity);
  }
} /* !lel::ecs */
