#include "EManagerEvent.hh"

namespace lel
{
  namespace ecs
  {
    namespace event
    {
      EManagerEvent::EManagerEvent(const Type t)
        : _t{t}
      {}

      EManagerEvent::Type EManagerEvent::getType() const
      {
        return _t;
      }

      EManagerEvent::Data EManagerEvent::getData() const
      {
        return _data;
      }
    } /* !event */
  } /* !ecs */
} /* !lel */
