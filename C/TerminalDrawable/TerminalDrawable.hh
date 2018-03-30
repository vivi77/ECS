#pragma once

#include "C/TerminalDrawable/terminaldrawable_export.h"
#include "C/CRTPC.hpp"
#include <bitset>

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      struct TERMINALDRAWABLE_EXPORT TerminalDrawable : public CRTPC<TerminalDrawable>
      {
        enum class Color
        {
          BLACK = 0,
          RED,
          GREEN,
          YELLOW,
          BLUE,
          MAGENTA,
          CYAN,
          WHITE,
        };

        enum Attributes
        {
          NORMAL = 0,
          BOLD = 1,
          DIM = BOLD << 1,
          UNDERLINED = DIM << 1,
          BLINK = UNDERLINED << 1,
          REVERSE = BLINK << 1,
          HIDDEN = REVERSE << 1,
        };

        using Attr = unsigned long long;

      public:
        TerminalDrawable(const char* = "");
        TerminalDrawable(const char*, const Color);
        TerminalDrawable(const char*, const Color, const Color);
        TerminalDrawable(const char*, const Color, const Color, const Attr);
        virtual ~TerminalDrawable() = default;

        const char* sym = "";
        Color fgColor = Color::WHITE;
        Color bgColor = Color::WHITE;
        std::bitset<6> attributes;
      };
    } /* !component */
  } /* !ecs */
} /* !lel */
