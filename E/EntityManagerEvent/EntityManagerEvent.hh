#pragma once

#include "E/CRTPE.hpp"
#include "E/EntityManagerEvent/entitymanagerevent_export.h"

namespace lel::ecs::event
{
  class ENTITYMANAGEREVENT_EXPORT EntityManagerEvent : public CRTPE<EntityManagerEvent>
  {
  public:
    using EntityID = unsigned; //EntityIDGenrator::ID

  public:
    enum class Type : char
    {
      ENTITY_CREATED,
      ENTITY_DESTROYED,
      ENTITY_NOT_FOUND,
    };

  public:
    EntityManagerEvent(const Type t);
    EntityManagerEvent(const Type t, const EntityID);
    ~EntityManagerEvent() override = default;

    Type getType() const;
    EntityID getEntityID() const;

  private:
    Type _t;
    EntityID _id;
  };
} /* !lel::ecs::event */
