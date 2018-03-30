#include "CLISystemEvent.hh"

namespace lel
{
  namespace ecs
  {
    namespace event
    {
      CLISystemEvent::CLISystemEvent(const Type t)
        : _t{t}
      {}

      CLISystemEvent::Type CLISystemEvent::getType() const
      {
        return _t;
      }
    } /* !event */
  } /* !ecs */
} /* !lel */
