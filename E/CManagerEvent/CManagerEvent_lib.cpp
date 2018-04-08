#include "E/CManagerEvent/CManagerEvent.hh"
#include "E/EIDGenerator/EIDGenerator.hh"
#include "E/EManager/EManager.hh"
#include "E/E_lib.hh"

namespace
{
  void destroy(lel::ecs::event::CManagerEvent* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  using CManagerEvent = lel::ecs::event::CManagerEvent;

  //CManagerEvent::assignID(lel::ecs::event::EIDGenerator::getSingleton().generateID());
  lel::ecs::event::EManager::registerEventDtor(CManagerEvent::getEventID(), (lel::ecs::event::EManager::Dtor)&destroy);
}

template struct EntryPointWrapper<lel::ecs::event::CManagerEvent>;
