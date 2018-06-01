#pragma once

#include "IDCounter.hpp"

namespace lel::ecs::event
{
  class IDEvent : public utility::IDCounter<IDEvent, unsigned>
  {
  public:
    IDEvent(const unsigned vl);
  };
} /* !lel::ecs::event */
