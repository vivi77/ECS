#include "DebugEvent.hh"

namespace lel::ecs::event
{
  DebugEvent::DebugEvent(const std::string& msg)
    : _msg{msg}
  {}

  std::string DebugEvent::getMessage() const
  {
    return _msg;
  }
} /* !lel::ecs::event */
