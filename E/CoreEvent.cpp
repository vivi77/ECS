#include "CoreEvent.hh"

CoreEvent::CoreEvent()
  : _type{Type::UNKNOWN}
  , _data{}
{
  // Do nothing
}

CoreEvent::CoreEvent(Type t)
  : _type{t}
  , _data{}
{
  // Do nothing
}

CoreEvent::CoreEvent(Type t, const std::string& data)
  : _type{t}
  , _data{data}
{
  // Do nothing
}

CoreEvent::Type CoreEvent::getType() const
{
  return _type;
}

std::string CoreEvent::getData() const
{
  return _data;
}

void CoreEvent::setType(const CoreEvent::Type type)
{
  _type = type;
}

void CoreEvent::setData(const std::string& data)
{
  _data = data;
}
