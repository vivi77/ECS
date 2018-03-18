#include "EManagerEvent.hh"
#include "EIDGenerator.hh"
#include "EManager.hh"
#include "E_lib.hh"

extern "C"
{
  EMANAGEREVENT_EXPORT IE* create()
  {
    return new EManagerEvent;
  }

  EMANAGEREVENT_EXPORT void destroy(IE* ptr)
  {
    delete ptr;
  }
}

static void setup()
{
  EManagerEvent::assignID(EIDGenerator::getSingleton().generateID());
  EManager::registerEventDtor(EManagerEvent::getEventID(), (EManager::Dtor)&destroy);
  EManager::fire<EManagerEvent>(EManagerEvent::Type::EVENT_ADDED, EManagerEvent::getEventID());
}

template struct EntryPointWrapper<EManagerEvent>;
