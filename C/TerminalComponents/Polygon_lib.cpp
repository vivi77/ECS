#include "Polygon.hh"
#include "C/C_lib.hh"
#include "C/CIDGenerator.hh"
#include "C/CManager/CManager.hh"
#include "E/EManager.hh"

namespace
{
  void destroy(lel::ecs::component::TerminalPolygon* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  using namespace lel::ecs::component;

  TerminalPolygon::assignID(CIDGenerator::getSingleton().generateID());
  CManager::registerCompDtor(TerminalPolygon::getComponentID(), (CManager::Dtor)&::destroy);
}

template struct EntryPointWrapper<lel::ecs::component::TerminalPolygon>;
