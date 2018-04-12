#include "DebugEvent.hh"
#include "E/EIDGenerator/EIDGenerator.hh"

namespace lel::ecs::event
{
  DebugEvent::ID DebugEvent::_id = EIDGenerator::_debugEventID;

  DebugEvent::DebugEvent(const std::string& msg)
    : _msg{msg}
  {}

  std::string DebugEvent::getMessage() const
  {
    return _msg;
  }

  DebugEvent::ID DebugEvent::getID() const
  {
    return getEventID();
  }

  DebugEvent::ID DebugEvent::getEventID()
  {
    return _id;
  }
} /* !lel::ecs::event */
