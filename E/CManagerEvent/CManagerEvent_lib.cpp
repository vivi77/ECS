#include "CManagerEvent.hh"
#include "EIDGenerator.hh"
#include "EManager.hh"
#include "E_lib.hh"

namespace
{
  void destroy(CManagerEvent* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  CManagerEvent::assignID(EIDGenerator::getSingleton().generateID());
  EManager::registerEventDtor(CManagerEvent::getEventID(), (EManager::Dtor)&destroy);
}

template struct EntryPointWrapper<CManagerEvent>;
