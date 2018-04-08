#include "E/CLISystemEvent/CLISystemEvent.hh"
#include "E/EIDGenerator/EIDGenerator.hh"
#include "E/EManager/EManager.hh"
#include "E/E_lib.hh"

namespace
{
  void destroy(lel::ecs::event::CLISystemEvent* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  using CLISystemEvent = lel::ecs::event::CLISystemEvent;

  //CLISystemEvent::assignID(lel::ecs::event::EIDGenerator::getSingleton().generateID());
  lel::ecs::event::EManager::registerEventDtor(CLISystemEvent::getEventID(), (lel::ecs::event::EManager::Dtor)&destroy);
}

template struct EntryPointWrapper<lel::ecs::event::CLISystemEvent>;
