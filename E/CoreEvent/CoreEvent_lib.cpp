#include "CoreEvent.hh"
#include "EManager.hh"
#include "EManagerEvent.hh"
#include "EIDGenerator.hh"
#include "E_lib.hh"

extern "C"
{
  COREEVENT_EXPORT IE* create()
  {
    return new CoreEvent;
  }

  COREEVENT_EXPORT void destroy(IE* ptr)
  {
    delete ptr;
  }
}

static void setup()
{
  CoreEvent::assignID(EIDGenerator::getSingleton().generateID());
  EManager::registerEventDtor(CoreEvent::getEventID(), (EManager::Dtor)&destroy);
  EManager::fire<EManagerEvent>(EManagerEvent::Type::EVENT_ADDED, CoreEvent::getEventID());
}

template struct EntryPointWrapper<CoreEvent>;
