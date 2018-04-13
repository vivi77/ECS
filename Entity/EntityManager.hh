#pragma once

#include "Entity.hh"
#include "EntityIDGenerator.hh"
#include "Entity/entitylogic_export.h"
#include "Utility/Fwd.hh"

namespace lel::ecs::entity
{
  class ENTITYLOGIC_EXPORT EntityManager
  {
  public:
    using EntityPtr = std::shared_ptr<Entity>;
    using ComponentPtr = Entity::CPtr;
    using ID = IDEntity;
    using SPtr = std::shared_ptr<system::IS>;

  public:
    EntityPtr createEntity(std::initializer_list<ComponentPtr>);
    void destroyEntity(const ID);
    void updateSysComponent(const SPtr&);

  private:
    std::vector<EntityPtr> _entities;
    EntityIDGenerator _idGenerator;
  };
} /* !lel::ecs::entity */
