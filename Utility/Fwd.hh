#pragma once

#include <memory>

namespace lel::ecs
{
  namespace system
  {
    using IDSystem = unsigned int;
  } /* !system */

  namespace component
  {
    using IDComponent = unsigned short;
  } /* !component */

  namespace event
  {
    using IDEvent = unsigned int;
  } /* !event */

  namespace utility
  {
    template <typename ID>
    class IIDGenerator;
  }
} /* !lel::ecs */

template <typename ID>
std::unique_ptr<lel::ecs::utility::IIDGenerator<ID>> createGenerator();
