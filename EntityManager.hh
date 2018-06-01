#pragma once

#include "Entity.hh"
#include "EntityIDGenerator.hh"
#include "Utility/Fwd.hh"

namespace lel::ecs::entity
{
  class EntityManager
  {
  public:
    using EntityPtr = std::shared_ptr<Entity>;
    using ComponentPtr = Entity::CPtr;
    using ID = IDEntity;
    using SPtr = std::shared_ptr<system::IS>;

  public:
    EntityPtr createEntity(std::initializer_list<ComponentPtr>);
    bool destroyEntity(const ID);
    void tryRegisterEntitiesInSystem(const SPtr&);
    EntityPtr fetchEntity(const ID&);

  private:
    std::vector<EntityPtr> _entities;
    EntityIDGenerator _idGenerator;
  };
} /* !lel::ecs::entity */
