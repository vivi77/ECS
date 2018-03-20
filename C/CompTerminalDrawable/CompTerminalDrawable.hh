#pragma once

#include "compterminaldrawable_export.h"

struct CompTerminalDrawable
{
  struct Pos
  {
    int x = 0;
    int y = 0;
  };

  enum class Color
  {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
  };

public:
  CompTerminalDrawable(const int, const int, const char*, const Color);

  Pos pos;
  const char* sym = "";
  Color color = Color::WHITE;
};
