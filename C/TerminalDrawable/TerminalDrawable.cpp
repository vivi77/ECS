#include "TerminalDrawable.hh"

TerminalDrawable::TerminalDrawable(const char* c)
  : sym{c}
{}

TerminalDrawable::TerminalDrawable(const char* c, const Color fg)
  : sym{c}
  , fgColor{fg}
{}

TerminalDrawable::TerminalDrawable(const char* c, const Color fg, const Color bg)
  : sym{c}
  , fgColor{fg}
  , bgColor{bg}
{}

TerminalDrawable::TerminalDrawable(const char* c, const Color fg, const Color bg, const Attr attr)
  : sym{c}
  , fgColor{fg}
  , bgColor{bg}
  , attributes{attr}
{}
