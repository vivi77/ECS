#include "TerminalText.hh"
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
  using TerminalText = lel::ecs::component::TerminalText;
  using CManager = lel::ecs::component::CManager;

  TerminalText::assignID(lel::ecs::component::CIDGenerator::getSingleton().generateID());
  CManager::registerCompDtor(TerminalText::getComponentID(), (CManager::Dtor)&::destroy);
}

template struct EntryPointWrapper<lel::ecs::component::TerminalText>;
