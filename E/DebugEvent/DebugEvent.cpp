#include "DebugEvent.hh"
#include "E/EIDGenerator/EIDGenerator.hh"
#include "Utility/TemplateUniqueID.hpp"

namespace lel::ecs::event
{
  DebugEvent::ID DebugEvent::_id = 0;

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
