#pragma once

#include "C/CompTerminalDrawable/compterminaldrawable_export.h"
#include "C/CRTPC.hpp"

struct COMPTERMINALDRAWABLE_EXPORT CompTerminalDrawable :
  public CRTPC<CompTerminalDrawable>
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
  CompTerminalDrawable(const char*);
  CompTerminalDrawable(const int, const int, const char*);
  CompTerminalDrawable(const int, const int, const char*, const Color);
  virtual ~CompTerminalDrawable() = default;

  Pos pos;
  const char* sym = "";
  Color color = Color::WHITE;
};
