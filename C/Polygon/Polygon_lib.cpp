#include "Polygon.hh"
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
  using Polygon = lel::ecs::component::Polygon;
  using CManager = lel::ecs::component::CManager;

  Polygon::assignID(lel::ecs::component::CIDGenerator::getSingleton().generateID());
  CManager::registerCompDtor(lel::ecs::component::Polygon::getComponentID(), (CManager::Dtor)&::destroy);
}

template struct EntryPointWrapper<lel::ecs::component::Polygon>;
