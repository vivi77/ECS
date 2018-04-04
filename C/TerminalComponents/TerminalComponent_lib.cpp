#include "Polygon.hh"
#include "Text.hh"
#include "C/C_lib.hh"
#include "C/CIDGenerator.hh"
#include "C/CManager/CManager.hh"

namespace
{
  void destroyPoly(lel::ecs::component::TerminalPolygon* ptr)
  {
    delete ptr;
  }

  void destroyText(lel::ecs::component::TerminalText* ptr)
  {
    delete ptr;
  }
} /* ! */

//static void setup()
//{
  //using namespace lel::ecs::component;

  //std::cout << "setup\n";
  //CManager::registerCompDtor(TerminalPolygon::getComponentID(), (CManager::Dtor)&::destroyPoly);
  //std::cout << TerminalPolygon::getComponentID() << " -\n";
  //CManager::registerCompDtor(TerminalText::getComponentID(), (CManager::Dtor)&::destroyText);
  //std::cout << TerminalText::getComponentID() << " =\n";
  //std::cout << "end\n";
//}

//template struct EntryPointWrapper<lel::ecs::component::TerminalPolygon, lel::ecs::component::TerminalText>;
