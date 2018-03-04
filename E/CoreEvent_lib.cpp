#include "CoreEvent.hh"
#include "E_lib.hh"
#include "EIDGenerator.hh"

static void assignID()
{
  CoreEvent::assignID(EIDGenerator::getSingleton().generateID());
}

template struct EntryPointWrapper<CoreEvent>;

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
