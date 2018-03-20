#include "CompTerminalDrawable.hh"

CompTerminalDrawable::CompTerminalDrawable(const int x, const int y, const char* c, const Color clr)
  : pos{x, y}
  , sym{c}
  , color{clr}
{}
