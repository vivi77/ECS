#pragma once

#include "C/TerminalDrawable/terminaldrawable_export.h"
#include "C/CRTPC.hpp"

struct TERMINALDRAWABLE_EXPORT TerminalDrawable : public CRTPC<TerminalDrawable>
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
  TerminalDrawable(const char*);
  TerminalDrawable(const int, const int, const char*);
  TerminalDrawable(const int, const int, const char*, const Color);
  virtual ~TerminalDrawable() = default;

  Pos pos;
  const char* sym = "";
  Color color = Color::WHITE;
};
