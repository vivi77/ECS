#include "EntityManager.hh"
#include "EntityIDGenerator.hh"
#include "S/CoreSystemProxy/CoreSystemProxy.hh"
#include "E/EntityManagerEvent/EntityManagerEvent.hh"
#include "E/EManager.hh"
#include <algorithm>

std::vector<EntityManager::EntityPtr> EntityManager::_entities;

EntityManager::EntityPtr EntityManager::createEntity(std::initializer_list<ComponentPtr> comps)
{
  _entities.emplace_back(std::make_shared<Entity>(EntityIDGenerator::generateID(), comps));
  EManager::fire<EntityManagerEvent>(EntityManagerEvent::Type::ENTITY_CREATED, _entities.back()->getID());
  CoreSystemProxy::registerEntityInSystems(_entities.back());
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
  if (it == endIt)
    EManager::fire<EntityManagerEvent>(EntityManagerEvent::Type::ENTITY_NOT_FOUND, id);
  else
  {
    _entities.erase(it);
    EManager::fire<EntityManagerEvent>(EntityManagerEvent::Type::ENTITY_DESTROYED, id);
  }
}

void EntityManager::updateSysComponent(const SPtr& sys)
{
  for (const auto& e : _entities)
    sys->registerEntity(e);
}
