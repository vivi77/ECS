#include "DebugEvent.hh"

namespace
{
  void destroy(lel::ecs::event::DebugEvent* ptr)
  {
    delete ptr;
  }
} /* ! */
