#include "EntityManagerEvent.hh"
#include "E/EIDGenerator.hh"
#include "E/EManager.hh"
#include "E/E_lib.hh"

namespace
{
  void destroy(EntityManagerEvent* ptr)
  {
    delete ptr;
  }
}

static void setup()
{
  EntityManagerEvent::assignID(EIDGenerator::getSingleton().generateID());
  EManager::registerEventDtor(EntityManagerEvent::getEventID(), (EManager::Dtor)&destroy);
}

template struct EntryPointWrapper<EntityManagerEvent>;
