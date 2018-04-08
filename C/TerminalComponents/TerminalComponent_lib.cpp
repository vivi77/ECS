#include "Polygon.hh"
#include "Text.hh"
#include "C/C_lib.hh"

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
