#pragma once

#include "entitylogic_export.h"
#include "Entity.hh"
#include "EntityIDGenerator.hh"

class ENTITYLOGIC_EXPORT EntityManager
{
public:
  using EntityPtr = std::shared_ptr<Entity>;
  using ComponentPtr = Entity::CPtr;
  using ID = EntityIDGenerator::ID;

public:
  static EntityPtr createEntity(std::initializer_list<ComponentPtr>);
  static void destroyEntity(const ID);

private:
  static std::vector<EntityPtr> _entities;
};
