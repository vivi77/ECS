#include "CoreEvent.hh"
#include "E_lib.hh"
#include "EIDGenerator.hh"
#include "EManager.hh"
#include <iostream>

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
}

template struct EntryPointWrapper<CoreEvent>;
