#include "CManagerEvent.hh"
#include "EIDGenerator.hh"
#include "EManager.hh"
#include "E_lib.hh"

extern "C"
{
  CMANAGEREVENT_EXPORT IE* create()
  {
    return new CManagerEvent;
  }

  CMANAGEREVENT_EXPORT void destroy(IE* ptr)
  {
    delete ptr;
  }
}

static void setup()
{
  CManagerEvent::assignID(EIDGenerator::getSingleton().generateID());
  EManager::registerEventDtor(CManagerEvent::getEventID(), (EManager::Dtor)&destroy);
  EManager::fire<EManagerEvent>(EManagerEvent::Type::EVENT_ADDED, CManagerEvent::getEventID());
}

template struct EntryPointWrapper<CManagerEvent>;
