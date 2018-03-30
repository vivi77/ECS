#pragma once

#include "Entity/entitylogic_export.h"
#include "Entity.hh"
#include "EntityIDGenerator.hh"
#include "S/IS.hh"

namespace lel
{
  namespace ecs
  {
    namespace entity
    {
      class ENTITYLOGIC_EXPORT EntityManager
      {
      public:
        using EntityPtr = std::shared_ptr<Entity>;
        using ComponentPtr = Entity::CPtr;
        using ID = EntityIDGenerator::ID;
        using SPtr = std::shared_ptr<system::IS>;

      public:
        static EntityPtr createEntity(std::initializer_list<ComponentPtr>);
        static void destroyEntity(const ID);
        static void updateSysComponent(const SPtr&);

      private:
        static std::vector<EntityPtr> _entities;
      };
    } /* !event */
  } /* !ecs */
} /* !lel */
