#include "EManagerEvent.hh"

EManagerEvent::EManagerEvent(const Type t)
  : _t{t}
{}

EManagerEvent::EManagerEvent(const Type t, ID id)
  : _t{t}
  , _idData{id}
{}

EManagerEvent::Type EManagerEvent::getType() const
{
  return _t;
}
