#pragma once

#include "Utility/Fwd.hh"
#include <memory>

namespace lel::ecs::event
{
  class IEListener
  {
  public:
    using EPtr = std::shared_ptr<IE>;

  public:
    virtual ~IEListener() = default;
    virtual void update(const EPtr&) = 0;
  };
} /* !lel::ecs::event */
