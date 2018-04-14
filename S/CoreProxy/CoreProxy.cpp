#include "CoreProxy.hh"
#include "E/EntityManagerEvent/EntityManagerEvent.hh"
#include "S/IS.hh"

namespace lel::ecs
{
  CoreProxy::CoreProxy(SystemContainer& systems, entity::EntityManager& manager, event::EManager& eventManager)
    : _systems{systems}
    , _entityManager{manager}
    , _eventManager{eventManager}
  {}

  entity::EntityManager::EntityPtr CoreProxy::createEntity(std::initializer_list<entity::EntityManager::ComponentPtr> il)
  {
    auto entity = _entityManager.createEntity(il);
    registerEntityInSystems(entity);
    _eventManager.fire<event::EntityManagerEvent>(event::EntityManagerEvent::Type::ENTITY_CREATED, entity->getID());
    return entity;
  }

  void CoreProxy::destroyEntity(const entity::EntityManager::ID id)
  {
    // TODO: Remove Entity from systems
    //   NB: There is no deregisterEntity in System interface... ... ...

    auto eventType = event::EntityManagerEvent::Type::ENTITY_NOT_FOUND;
    if (_entityManager.destroyEntity(id))
      eventType = event::EntityManagerEvent::Type::ENTITY_DESTROYED;
    _eventManager.fire<event::EntityManagerEvent>(eventType, id);
  }

  void CoreProxy::registerEntityInSystems(const std::shared_ptr<entity::Entity>& entity)
  {
    for (auto& data : _systems)
      data.sys->registerEntity(entity);
  }
} /* !lel::ecs */
