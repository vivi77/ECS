#include "CoreProxy.hh"
#include "E/EntityManagerEvent/EntityManagerEvent.hh"
#include "S/IS.hh"

namespace
{
  template <typename Fct>
  inline void applyOnSystemVector(lel::ecs::CoreProxy::SystemContainer& systems, Fct&& fct)
  {
    std::for_each(std::begin(systems), std::end(systems), std::forward<Fct>(fct));
  }
} /* ! */

namespace lel::ecs
{
  CoreProxy::CoreProxy(SystemContainer& systems,
                       entity::EntityManager& manager,
                       event::EManager& eventManager,
                       bool& quit)
    : _systems{systems}
    , _entityManager{manager}
    , _eventManager{eventManager}
    , _quit{quit}
  {}

  entity::EntityManager::EntityPtr CoreProxy::createEntity(std::initializer_list<entity::EntityManager::ComponentPtr> il)
  {
    using EME = event::EntityManagerEvent;

    auto entity = _entityManager.createEntity(il);
    // Try to register the new entity into all existing system
    std::for_each(std::begin(_systems),
                  std::end(_systems),
                  [&entity](auto& data)
                  { data.sys->registerEntity(entity); });
    _eventManager.fire<EME>(EME::Type::ENTITY_CREATED, entity->getID());
    return entity;
  }

  void CoreProxy::destroyEntity(const entity::EntityManager::ID id)
  {
    using EME = event::EntityManagerEvent;

    auto eventType = EME::Type::ENTITY_NOT_FOUND;

    auto entityToDelete = _entityManager.fetchEntity(id);
    if (entityToDelete != nullptr)
    {
      std::for_each(std::begin(_systems),
                    std::end(_systems),
                    [&entityToDelete](auto& data)
                    { data.sys->deregisterEntity(entityToDelete); });

      if (_entityManager.destroyEntity(id))
        eventType = EME::Type::ENTITY_DESTROYED;
    }
    _eventManager.fire<EME>(eventType, id);
  }

  void CoreProxy::stopCore()
  {
    _quit = true;
  }

  void CoreProxy::addSystem(const std::string& path)
  {
    _systemsToAdd.emplace_back(path);
  }

  void CoreProxy::removeSystem(const std::string& path)
  {
    _systemsToRemove.emplace_back(path);
  }

  void CoreProxy::reloadSystem(const std::string& path)
  {
    _systemsToReload.emplace_back(path);
  }
} /* !lel::ecs */
