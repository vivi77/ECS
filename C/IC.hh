#pragma once

namespace lel::ecs::component
{
  class IC
  {
  public:
    using ID = unsigned;

  public:
    virtual ~IC() = default;
    virtual ID getID() const = 0;
  };
} /* !lel::eccs::component */
