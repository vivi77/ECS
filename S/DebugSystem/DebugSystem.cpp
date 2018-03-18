#include "DebugSystem.hh"

void DebugSystem::exec()
{
}

void DebugSystem::update(const EPtr& event)
{
  _log << "Event id" << event->getID() << " fired\n";
}
