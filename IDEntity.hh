#pragma once

#include "IDCounter.hpp"

namespace lel::ecs::entity
{
  class IDEntity : public utility::IDCounter<IDEntity, unsigned>
  {
  public:
    IDEntity(const unsigned vl);
  };
} /* !lel::ecs::entity */
