#include "EManagerEvent.hh"

namespace
{
  void destroy(lel::ecs::event::EManagerEvent* ptr)
  {
    delete ptr;
  }
} /* ! */
