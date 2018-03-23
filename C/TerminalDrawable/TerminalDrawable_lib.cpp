#include "TerminalDrawable.hh"
#include "C/C_lib.hh"
#include "C/CIDGenerator.hh"
#include "C/CManager/CManager.hh"
#include "E/EManager.hh"

namespace
{
  void destroy(IC* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  TerminalDrawable::assignID(CIDGenerator::getSingleton().generateID());
  CManager::registerCompDtor(TerminalDrawable::getComponentID(), (CManager::Dtor)&::destroy);
}

template struct EntryPointWrapper<TerminalDrawable>;
