#include "CoreEvent.hh"
#include "EManager.hh"
#include "EManagerEvent.hh"
#include "EIDGenerator.hh"
#include "E_lib.hh"

namespace
{
  void destroy(lel::ecs::event::CoreEvent* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  using CoreEvent = lel::ecs::event::CoreEvent;

  CoreEvent::assignID(lel::ecs::event::EIDGenerator::getSingleton().generateID());
  lel::ecs::event::EManager::registerEventDtor(CoreEvent::getEventID(), (lel::ecs::event::EManager::Dtor)&destroy);
}

template struct EntryPointWrapper<lel::ecs::event::CoreEvent>;
