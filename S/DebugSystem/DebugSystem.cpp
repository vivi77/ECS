#include "DebugSystem.hh"
#include "CoreEvent.hh"

namespace
{
  inline void requestEvent(lel::Log& log, const std::string& msg)
  {
    log << "\033[34m[ RQ ]" << msg;
  }

  inline void badEvent(lel::Log& log, const std::string& msg)
  {
    log << "\033[31m[ KO ]" << msg;
  }

  inline void okEvent(lel::Log& log, const std::string& msg)
  {
    log << "\033[32m[ OK ]" << msg;
  }

  inline void warnEvent(lel::Log& log, const std::string& msg)
  {
    log << "\033[33m[WARN]" << msg;
  }

  inline void infoEvent(lel::Log& log, const std::string& msg)
  {
    log << "[INFO]" << msg;
  }

  void debugCoreEvent(const std::shared_ptr<CoreEvent>& event, lel::Log& log)
  {
    switch (event->getType())
    {
      case CoreEvent::Type::ADD_SYSTEM:
        requestEvent(log, {"Add system '" + event->getData()[0] + "' requested"});
        break;
      case CoreEvent::Type::ADD_SYSTEM_FAILURE:
        badEvent(log, {"Cannot add system '" + event->getData()[0] + "'"});
        break;
      case CoreEvent::Type::ADD_SYSTEM_SUCCESS:
        okEvent(log, {"System '" + event->getData()[0] + "' added"});
        break;
      case CoreEvent::Type::ALREADY_ADDED_SYSTEM:
        warnEvent(log, {"System '" + event->getData()[0] + "' already added"});
        break;
      case CoreEvent::Type::CLOSING:
        infoEvent(log, "Program is closing. Wait for everything to be removed");
        break;
      case CoreEvent::Type::EXIT:
        requestEvent(log, "Closing program requested");
        break;
      case CoreEvent::Type::INVALID_SYSTEM:
        badEvent(log, {"System from library '" + event->getData()[0]
                 + "' is not valid" + "\033[1;31mReason: " + event->getData()[1]});
        break;
      case CoreEvent::Type::REM_SYSTEM:
        requestEvent(log, "Remove system '" + event->getData()[0] + "' requested");
        break;
      case CoreEvent::Type::REM_SYSTEM_FAILURE:
        badEvent(log, {"Cannot remove system '" + event->getData()[0] + "'"});
        break;
      case CoreEvent::Type::REM_SYSTEM_SUCCESS:
        okEvent(log, {"System '" + event->getData()[0] + "' removed"});
        break;
      case CoreEvent::Type::SYSTEM_NOT_FOUND:
        badEvent(log, {"System '" + event->getData()[0] + "' not found"});
        break;
      case CoreEvent::Type::UNKNOWN:
        infoEvent(log, "Unknown event found");
      default:
        break;
    }
    log << "\033[0m\n";
  }
} /* ! */

void DebugSystem::exec()
{
}

void DebugSystem::update(const EPtr& event)
{
  if (event->getID() == CoreEvent::getEventID())
    debugCoreEvent(std::static_pointer_cast<CoreEvent>(event), _log);
  else
    _log << "Event id" << event->getID() << " fired\n";
}
