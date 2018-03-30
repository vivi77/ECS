#pragma once

#include "C/TerminalText/terminaltext_export.h"
#include "C/CRTPC.hpp"
#include "C/TemplateText/TemplateText.hpp"
#include <bitset>

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      struct TerminalColor
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
        TerminalColor(const Color fg = Color::WHITE, const Color bg = Color::WHITE, const Attr attr = 0);

      public:
        Color fgColor = Color::WHITE;
        Color bgColor = Color::WHITE;
        std::bitset<6> attributes;
      };

      // Should use type-alias but there cannot export the class
      struct TERMINALTEXT_EXPORT TerminalText : public TemplateText<TerminalColor>
      {
      public:
        template <typename ... Args>
        TerminalText(const char* text, Args&& ... args)
          : TemplateText{text, std::forward<Args>(args)...}
        {}
      };
    } /* !component */
  } /* !ecs */
} /* !lel */
