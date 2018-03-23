#pragma once

#include "C/TerminalDrawable/terminaldrawable_export.h"
#include "C/CRTPC.hpp"

struct TERMINALDRAWABLE_EXPORT TerminalDrawable : public CRTPC<TerminalDrawable>
{
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
  TerminalDrawable(const char*, const Color);
  virtual ~TerminalDrawable() = default;

  const char* sym = "";
  Color color = Color::WHITE;
};
