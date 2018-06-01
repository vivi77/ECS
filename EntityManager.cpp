#include "EntityManager.hh"
#include "IS.hh"
#include <algorithm>

namespace lel::ecs::entity
{
  EntityManager::EntityPtr EntityManager::createEntity(std::initializer_list<ComponentPtr> comps)
  {
    auto ent = std::make_shared<Entity>(_idGenerator.generateID(), comps);
    _entities.emplace_back(ent);
    return ent;
  }

  bool EntityManager::destroyEntity(const ID id)
  {
    auto beginIt = std::begin(_entities);
    auto endIt = std::end(_entities);
    auto pred = [&id](const auto& it) -> bool
          {
            return it->getID() == id;
          };
    auto it = std::find_if(beginIt, endIt, pred);
    if (it == endIt)
      return false;
    _entities.erase(it);
    return true;
  }

  // TODO: The name can be ambiguous
  void EntityManager::tryRegisterEntitiesInSystem(const SPtr& sys)
  {
    for (const auto& e : _entities)
      sys->registerEntity(e);
  }

  // TODO[HIGH PRIORITY]: Implement fetchEntity with a cache system.
  EntityManager::EntityPtr EntityManager::fetchEntity(const ID& id)
  {
    auto beginIt = std::begin(_entities);
    auto endIt = std::end(_entities);
    auto pred = [&id](const auto& ent) -> bool
          {
            return ent->getID() == id;
          };
    auto it = std::find_if(beginIt, endIt, pred);
    return it == endIt ? nullptr : *it;
  }
} /* !lel::ecs::entity */
