#pragma once

namespace lel::ecs::utility
{
  template <typename ID>
  class IIDGenerator
  {
  public:
    virtual ~IIDGenerator() = default;
    virtual ID generateID() = 0;
  };
} /* !lel::ecs::utility */
