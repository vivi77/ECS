#include "EntityManager.hh"
#include "S/IS.hh"
#include "E/EntityManagerEvent/EntityManagerEvent.hh"
#include "E/EManager/EManager.hh"
#include <algorithm>

namespace lel::ecs::entity
{
  EntityManager::EntityPtr ENTITYLOGIC_EXPORT EntityManager::createEntity(std::initializer_list<ComponentPtr> comps)
  {
    auto ent = std::make_shared<Entity>(_idGenerator.generateID(), comps);
    _entities.emplace_back(ent);
    event::EManager::fire<event::EntityManagerEvent>(event::EntityManagerEvent::Type::ENTITY_CREATED, ent->getID());
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
      // TODO: Remove Entity from systems
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
