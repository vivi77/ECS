#pragma once

#include "Entity/entitylogic_export.h"

namespace lel::ecs::entity
{
  class ENTITYLOGIC_EXPORT EntityIDGenerator
  {
  public:
    using ID = unsigned;

  public:
    static ID generateID();

  private:
    static ID _id;
  };
} /* !lel::ecs::entity */
