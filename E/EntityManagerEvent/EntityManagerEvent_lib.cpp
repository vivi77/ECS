#include "EntityManagerEvent.hh"
#include "E/EIDGenerator.hh"
#include "E/EManager.hh"
#include "E/E_lib.hh"

namespace
{
  void destroy(lel::ecs::event::EntityManagerEvent* ptr)
  {
    delete ptr;
  }
}

static void setup()
{
  using EntityManagerEvent = lel::ecs::event::EntityManagerEvent;

  EntityManagerEvent::assignID(lel::ecs::event::EIDGenerator::getSingleton().generateID());
  lel::ecs::event::EManager::registerEventDtor(EntityManagerEvent::getEventID(), (lel::ecs::event::EManager::Dtor)&destroy);
}

template struct EntryPointWrapper<lel::ecs::event::EntityManagerEvent>;
