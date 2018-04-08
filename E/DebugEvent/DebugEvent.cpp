#include "DebugEvent.hh"
#include "E/EIDGenerator.hh"
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

  // TODO: Will be removed
  void DebugEvent::assignID(const ID)
  {}
} /* !lel::ecs::event */
