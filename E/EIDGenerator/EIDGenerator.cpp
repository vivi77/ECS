#include "EIDGenerator.hh"

template <>
std::unique_ptr<lel::ecs::utility::IIDGenerator<lel::ecs::event::IDEvent>> EIDGEN_EXPORT createGenerator()
{
  return std::make_unique<lel::ecs::event::EIDGenerator>();
}

namespace lel::ecs::event
{
  EIDGenerator::ID EIDGenerator::generateID()
  {
    return _id++;
  }

  // DebugEvent
  EIDGenerator::ID EIDGenerator::DebugEvent::_id{0};

  EIDGenerator::DebugEvent::DebugEvent(const std::string& msg)
    : _msg{msg}
  {}

  std::string EIDGenerator::DebugEvent::getMessage() const
  {
    return _msg;
  }

  EIDGenerator::ID EIDGenerator::DebugEvent::getID() const
  {
    return getEventID();
  }

  EIDGenerator::ID EIDGenerator::DebugEvent::getEventID()
  {
    return _id;
  }
} /* !lel::ecs::event */
