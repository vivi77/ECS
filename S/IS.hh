#pragma once

#include "Entity/Entity.hh"
#include <memory>

namespace lel
{
  namespace ecs
  {
    namespace system
    {
      class IS
      {
      public:
        using ID = unsigned;
        using EntityPtr = std::shared_ptr<Entity>;

      public:
        virtual ~IS() = default;
        virtual void exec() = 0;
        virtual ID getID() const = 0;
        virtual bool isListener() const = 0;
        virtual void registerEntity(const EntityPtr&) = 0;
        virtual void setup() = 0;
        virtual void atRemove() = 0;
      };
    } /* !system */
  } /* !ecs */
} /* !lel */
