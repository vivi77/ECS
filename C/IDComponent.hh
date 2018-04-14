#pragma once

#include "Utility/IDCounter.hpp"

namespace lel::ecs::component
{
  class IDComponent : public utility::IDCounter<IDComponent, unsigned>
  {
  public:
    IDComponent(const unsigned);
  };
} /* !lel::ecs::component */
