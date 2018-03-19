#include "EntityManager.hh"
#include "EntityIDGenerator.hh"
#include <algorithm>

std::vector<EntityManager::EntityPtr> EntityManager::_entities;

EntityManager::EntityPtr EntityManager::createEntity(std::initializer_list<ComponentPtr> comps)
{
  _entities.emplace_back(std::make_shared<Entity>(EntityIDGenerator::generateID(), comps));
  return _entities.back();
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
  if (it != endIt)
    _entities.erase(it);
}

void EntityManager::updateSysComponent(const SPtr& sys)
{
  for (const auto& e : _entities)
    sys->registerEntity(e);
}
