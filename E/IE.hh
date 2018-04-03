#pragma once

namespace lel::ecs::event
{
  class IE
  {
  public:
    using ID = unsigned;

  public:
    virtual ~IE() = default;
    virtual ID getID() const = 0;
  };
} /* !lel::ecs::event */
