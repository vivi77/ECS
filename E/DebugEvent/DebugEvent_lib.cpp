#include "E/DebugEvent/DebugEvent.hh"
#include "E/EIDGenerator.hh"
#include "E/EManager.hh"
#include "E/E_lib.hh"
#include <iostream>

namespace
{
  void destroy(lel::ecs::event::DebugEvent* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  using namespace lel::ecs::event;

  //DebugEvent::assignID(EIDGenerator::getSingleton().generateID());
  EManager::registerEventDtor(DebugEvent::getEventID(), (EManager::Dtor)&destroy);
}

template struct EntryPointWrapper<lel::ecs::event::DebugEvent>;
