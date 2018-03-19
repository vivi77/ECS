#include "Entity.hh"
#include <algorithm>

Entity::Entity(const ID id, std::initializer_list<CPtr> li)
  : _id{id}
  , _components{li}
{}

Entity::ID Entity::getID() const
{
  return _id;
}

Entity::CContainer& Entity::accessComponents()
{
  return _components;
}

void Entity::addComponent(const CPtr& comp)
{
  auto beginIt = std::begin(_components);
  auto endIt = std::end(_components);
  auto pred = [&comp](const auto& it) -> bool
        {
          return it->getID() == comp->getID();
        };
  auto it = std::find_if(beginIt, endIt, pred);
  if (it == endIt)
    _components.emplace_back(comp);
}

void Entity::removeComponent(const IC::ID id)
{
  auto beginIt = std::begin(_components);
  auto endIt = std::end(_components);
  auto pred = [&id](const auto& it) -> bool
        {
          it->getID() == id;
        };
  auto it = std::find_if(beginIt, endIt, pred);
  if (it != endIt)
    _components.erase(it);
}