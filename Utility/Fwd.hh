#pragma once

#include <memory>

// TODO: Change to make all ID* classes works as integer without them colliding
// or it will cause compiler to consider all those ID* classes as same if they
// have the same type.
namespace lel::ecs
{
  namespace system
  {
    using IDSystem = unsigned int;
  } /* !system */

  namespace component
  {
    using IDComponent = unsigned short;
    class IC;
  } /* !component */

  namespace event
  {
    using IDEvent = unsigned long;
    class IE;
    class IEListener;
  } /* !event */

  namespace entity
  {
    using IDEntity = unsigned long long;
  } /* !entity */

  namespace utility
  {
    template <typename ID>
    class IIDGenerator;
  }
} /* !lel::ecs */

template <typename ID>
std::unique_ptr<lel::ecs::utility::IIDGenerator<ID>> createGenerator();
