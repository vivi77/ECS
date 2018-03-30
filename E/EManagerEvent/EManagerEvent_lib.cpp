#include "EManagerEvent.hh"
#include "EIDGenerator.hh"
#include "EManager.hh"
#include "E_lib.hh"

namespace
{
  void destroy(lel::ecs::event::EManagerEvent* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  using EManagerEvent = lel::ecs::event::EManagerEvent;

  EManagerEvent::assignID(lel::ecs::event::EIDGenerator::getSingleton().generateID());
  lel::ecs::event::EManager::registerEventDtor(EManagerEvent::getEventID(), (lel::ecs::event::EManager::Dtor)&destroy);
}

template struct EntryPointWrapper<lel::ecs::event::EManagerEvent>;
