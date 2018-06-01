#pragma once

#include "Entity.hh"

namespace lel::ecs::system
{
  class IS
  {
  public:
    using ID = IDSystem;
    using EntityPtr = std::shared_ptr<entity::Entity>;

  public:
    virtual ~IS() = default;
    virtual void exec() = 0;
    virtual ID getID() const = 0;
    virtual bool isListener() const = 0;
    virtual void registerEntity(const EntityPtr&) = 0;
    virtual void deregisterEntity(const EntityPtr&) = 0;
    virtual void setup() = 0;
    virtual void atRemove() = 0;
  };
} /* !lel::ecs::system */
