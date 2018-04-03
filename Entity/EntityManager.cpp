#include "EntityManager.hh"
#include "EntityIDGenerator.hh"
#include "S/CoreSystemProxy/CoreSystemProxy.hh"
#include "E/EntityManagerEvent/EntityManagerEvent.hh"
#include "E/EManager.hh"
#include <algorithm>

namespace lel::ecs::entity
{
  std::vector<EntityManager::EntityPtr> EntityManager::_entities;

  EntityManager::EntityPtr EntityManager::createEntity(std::initializer_list<ComponentPtr> comps)
  {
    auto ent = std::make_shared<Entity>(EntityIDGenerator::generateID(), comps);
    _entities.emplace_back(ent);
    event::EManager::fire<event::EntityManagerEvent>(event::EntityManagerEvent::Type::ENTITY_CREATED, ent->getID());
    CoreSystemProxy::registerEntityInSystems(ent);
    return ent;
  }

  void EntityManager::destroyEntity(const ID id)
  {
    auto beginIt = std::begin(_entities);
    auto endIt = std::end(_entities);
    auto pred = [&id](const auto& it) -> bool
          {
            return it->getID() == id;
          };
    auto it = std::find_if(beginIt, endIt, pred);
    if (it == endIt)
      event::EManager::fire<event::EntityManagerEvent>(event::EntityManagerEvent::Type::ENTITY_NOT_FOUND, id);
    else
    {
      // TODO: Remove Entitty from systems
      _entities.erase(it);
      event::EManager::fire<event::EntityManagerEvent>(event::EntityManagerEvent::Type::ENTITY_DESTROYED, id);
    }
  }

  void EntityManager::updateSysComponent(const SPtr& sys)
  {
    for (const auto& e : _entities)
      sys->registerEntity(e);
  }
} /* !lel::ecs::entity */
