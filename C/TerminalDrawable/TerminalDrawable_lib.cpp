#include "TerminalDrawable.hh"
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
  using TerminalDrawable = lel::ecs::component::TerminalDrawable;
  using CManager = lel::ecs::component::CManager;

  TerminalDrawable::assignID(lel::ecs::component::CIDGenerator::getSingleton().generateID());
  CManager::registerCompDtor(TerminalDrawable::getComponentID(), (CManager::Dtor)&::destroy);
}

template struct EntryPointWrapper<lel::ecs::component::TerminalDrawable>;
