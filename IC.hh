#pragma once

#include "Utility/Fwd.hh"

namespace lel::ecs::component
{
  class IC
  {
  public:
    using ID = IDComponent;

  public:
    virtual ~IC() = default;
    virtual ID getID() const = 0;
    virtual void setEntityOwner(const entity::IDEntity&) = 0;
  };
} /* !lel::eccs::component */
