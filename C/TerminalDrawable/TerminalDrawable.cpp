#include "TerminalDrawable.hh"

TerminalDrawable::TerminalDrawable(const char* c)
  : sym{c}
{}

TerminalDrawable::TerminalDrawable(const char* c, const Color clr)
  : sym{c}
  , color{clr}
{}
