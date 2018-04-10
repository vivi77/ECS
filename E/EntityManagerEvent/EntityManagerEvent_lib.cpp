#include "EntityManagerEvent.hh"

namespace
{
  void destroy(lel::ecs::event::EntityManagerEvent* ptr)
  {
    delete ptr;
  }
}
