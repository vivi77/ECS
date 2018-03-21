#include "CLISystemEvent.hh"
#include "EIDGenerator.hh"
#include "EManager.hh"
#include "E_lib.hh"

namespace
{
  void destroy(CLISystemEvent* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  CLISystemEvent::assignID(EIDGenerator::getSingleton().generateID());
  EManager::registerEventDtor(CLISystemEvent::getEventID(), (EManager::Dtor)&destroy);
}

template struct EntryPointWrapper<CLISystemEvent>;
