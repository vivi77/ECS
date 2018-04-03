#pragma once

#include <bitset>

namespace lel::ecs::component
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
    TerminalColor(const Color fg = Color::WHITE, const Color bg = Color::BLACK, const Attr attr = 0);

  public:
    Color fgColor = Color::WHITE;
    Color bgColor = Color::BLACK;
    std::bitset<6> attributes;
  };
} /* !lel::ecs::component */
