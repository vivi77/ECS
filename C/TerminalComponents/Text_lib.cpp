#include "Text.hh"
#include "C/C_lib.hh"
#include "C/CIDGenerator.hh"
#include "C/CManager/CManager.hh"
#include "E/EManager.hh"

namespace
{
  void destroy(lel::ecs::component::IC* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  using namespace lel::ecs::component;

  TerminalText::assignID(CIDGenerator::getSingleton().generateID());
  CManager::registerCompDtor(TerminalText::getComponentID(), (CManager::Dtor)&::destroy);
}

template struct EntryPointWrapper<lel::ecs::component::TerminalText>;
