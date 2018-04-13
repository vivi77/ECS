#include "CoreSystemProxy.hh"
#include "S/IS.hh"

namespace lel::ecs
{
  CoreSystemProxy::SystemContainer* CoreSystemProxy::_systems = nullptr;
  entity::EntityManager* CoreSystemProxy::_entityManager = nullptr;

  void CoreSystemProxy::setSystemsList(SystemContainer& systems)
  {
    if (_systems != nullptr)
      return ;
    _systems = &systems;
  }

  entity::EntityManager::EntityPtr CoreSystemProxy::createEntity(std::initializer_list<entity::EntityManager::ComponentPtr> il)
  {
    if (!_entityManager)
      return nullptr;

    auto entity = _entityManager->createEntity(il);
    registerEntityInSystems(entity);
    return entity;
  }

  void CoreSystemProxy::registerEntityInSystems(const std::shared_ptr<entity::Entity>& entity)
  {
    if (!_systems)
      return ;

    for (auto& data : *_systems)
      data.sys->registerEntity(entity);
  }

  void CoreSystemProxy::setEntityManager(entity::EntityManager& manager)
  {
    if (_entityManager != nullptr)
      return ;
    _entityManager = &manager;
  }
} /* !lel::ecs */
