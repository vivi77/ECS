#include "TerminalText.hh"

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      TerminalColor::TerminalColor(const Color fg, const Color bg, const Attr attr)
        : fgColor{fg}
        , bgColor{bg}
        , attributes{attr}
      {}
    } /* !component */
  } /* !ecs */
} /* !lel */
