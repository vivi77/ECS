#pragma once

#include "Entity/entitylogic_export.h"
#include "Entity.hh"
#include "Utility/Fwd.hh"

namespace lel::ecs::entity
{
  // TODO: Make the manager not being a singleton.
  //    ==> Reason: Does not match with the will to have several different
  //    instance of a 'Core' class.
  class ENTITYLOGIC_EXPORT EntityManager
  {
  public:
    using EntityPtr = std::shared_ptr<Entity>;
    using ComponentPtr = Entity::CPtr;
    using ID = IDEntity;
    using SPtr = std::shared_ptr<system::IS>;

  public:
    static EntityPtr createEntity(std::initializer_list<ComponentPtr>);
    static void destroyEntity(const ID);
    static void updateSysComponent(const SPtr&);

  private:
    static std::vector<EntityPtr> _entities;
  };
} /* !lel::ecs::entity */
