#pragma once

#include "Utility/Fwd.hh"

namespace lel::ecs::event
{
  class IE
  {
  public:
    using ID = IDEvent;

  public:
    virtual ~IE() = default;
    virtual ID getID() const = 0;
  };
} /* !lel::ecs::event */
