#include "EManagerEvent.hh"
#include "EIDGenerator.hh"
#include "EManager.hh"
#include "E_lib.hh"

namespace
{
  void destroy(EManagerEvent* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  EManagerEvent::assignID(EIDGenerator::getSingleton().generateID());
  EManager::registerEventDtor(EManagerEvent::getEventID(), (EManager::Dtor)&destroy);
  EManager::fire<EManagerEvent>(EManagerEvent::Type::EVENT_ADDED, EManagerEvent::getEventID());
}

template struct EntryPointWrapper<EManagerEvent>;
