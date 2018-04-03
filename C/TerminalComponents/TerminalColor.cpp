#include "TerminalColor.hh"

namespace lel::ecs::component
{
  TerminalColor::TerminalColor(const Color fg, const Color bg, const Attr attr)
    : fgColor{fg}
    , bgColor{bg}
    , attributes{attr}
  {}
} /* !lel::ecs::component */
