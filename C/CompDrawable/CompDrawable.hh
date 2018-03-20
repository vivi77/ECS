#pragma once

#include "compdrawable_export.h"

class CompDrawable
{
  struct Pos
  {
    int x;
    int y;
    int z;
  };

public:
  CompDrawable(const int x, const int y, const int z);

private:
  Pos _pos;
};
