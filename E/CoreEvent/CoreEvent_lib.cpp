#include "CoreEvent.hh"

namespace
{
  void destroy(lel::ecs::event::CoreEvent* ptr)
  {
    delete ptr;
  }
} /* ! */
