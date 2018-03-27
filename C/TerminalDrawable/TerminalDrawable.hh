#pragma once

#include "C/TerminalDrawable/terminaldrawable_export.h"
#include "C/CRTPC.hpp"

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

public:
  TerminalDrawable(const char* = "");
  TerminalDrawable(const char*, const Color);
  TerminalDrawable(const char*, const Color, const Color);
  virtual ~TerminalDrawable() = default;

  const char* sym = "";
  Color fgColor = Color::WHITE;
  Color bgColor = Color::WHITE;
};
