#include "CLISystemEvent.hh"

namespace lel::ecs::event
{
  CLISystemEvent::CLISystemEvent(const Type t)
    : _t{t}
  {}

  CLISystemEvent::Type CLISystemEvent::getType() const
  {
    return _t;
  }
} /* !lel */
