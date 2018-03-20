#include "CompTerminalDrawable.hh"
#include "C/C_lib.hh"
#include "C/CIDGenerator.hh"
#include "C/CManager/CManager.hh"
#include "E/EManager.hh"

void destroy(IC* ptr)
{
  delete ptr;
}

static void setup()
{
  CompTerminalDrawable::assignID(CIDGenerator::getSingleton().generateID());
  CManager::registerCompDtor(CompTerminalDrawable::getComponentID(), (CManager::Dtor)&destroy);
  EManager::fire<CManagerEvent>(CManagerEvent::Type::COMP_ADDED, CompTerminalDrawable::getComponentID());
}

template struct EntryPointWrapper<CompTerminalDrawable>;
