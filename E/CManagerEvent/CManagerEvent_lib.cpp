#include "E/CManagerEvent/CManagerEvent.hh"

namespace
{
  void destroy(lel::ecs::event::CManagerEvent* ptr)
  {
    delete ptr;
  }
} /* ! */
