#pragma once

#include "Utility/IDCounter.hpp"

namespace lel::ecs::system
{
  class IDSystem : public utility::IDCounter<IDSystem, unsigned>
  {
  public:
    IDSystem(const unsigned);
  };
} /* !lel::ecs::system */
