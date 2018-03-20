#include "EntityManager.hh"
#include <algorithm>

EntityManager::EntityPtr EntityManager::createEntity(std::initializer_list<ComponentPtr> comps)
{
  _entities.emplace_back(std::make_shared<Entity>(comps));
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
