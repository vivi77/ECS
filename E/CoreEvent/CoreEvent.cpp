#include "CoreEvent.hh"

namespace lel::ecs::event
{
  CoreEvent::CoreEvent(Type t)
    : _type{t}
    , _data{}
  {}

  CoreEvent::CoreEvent(Type t, const std::string& data)
    : _type{t}
    , _data{data}
  {}

  CoreEvent::Type CoreEvent::getType() const
  {
    return _type;
  }

  std::vector<std::string> CoreEvent::getData() const
  {
    return _data;
  }
} /* !lel::ecs::event */
