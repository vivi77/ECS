#include "TerminalDrawable.hh"

TerminalDrawable::TerminalDrawable(const char* c)
  : sym{c}
{}

TerminalDrawable::TerminalDrawable(const int x, const int y, const char* c)
  : pos{x, y}
  , sym{c}
{}

TerminalDrawable::TerminalDrawable(const int x, const int y, const char* c, const Color clr)
  : pos{x, y}
  , sym{c}
  , color{clr}
{}
