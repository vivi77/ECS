#include "CompTerminalDrawable.hh"

CompTerminalDrawable::CompTerminalDrawable(const char* c)
  : sym{c}
{}

CompTerminalDrawable::CompTerminalDrawable(const int x, const int y, const char* c)
  : pos{x, y}
  , sym{c}
{}

CompTerminalDrawable::CompTerminalDrawable(const int x, const int y, const char* c, const Color clr)
  : pos{x, y}
  , sym{c}
  , color{clr}
{}
