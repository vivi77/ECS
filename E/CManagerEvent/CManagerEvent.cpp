#include "E/CManagerEvent/CManagerEvent.hh"

namespace lel::ecs::event
{
  CManagerEvent::CManagerEvent(const Type t)
    : _t{t}
  {}

  CManagerEvent::Type CManagerEvent::getType() const
  {
    return _t;
  }

  CManagerEvent::Data CManagerEvent::getData() const
  {
    return _data;
  }
} /* !lel::ecs::event */
