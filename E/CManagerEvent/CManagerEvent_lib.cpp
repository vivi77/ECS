#include "CManagerEvent.hh"
#include "EIDGenerator.hh"
#include "EManager.hh"
#include "E_lib.hh"

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
