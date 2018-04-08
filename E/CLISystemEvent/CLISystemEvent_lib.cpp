#include "CLISystemEvent.hh"
#include "E/EIDGenerator/EIDGenerator.hh"

namespace
{
  void destroy(lel::ecs::event::CLISystemEvent* ptr)
  {
    delete ptr;
  }
} /* ! */
