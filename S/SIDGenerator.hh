#pragma once

#include "sidgen_export.h"

class SIDGEN_EXPORT SIDGenerator
{
  using ID = unsigned;

public:
  static SIDGenerator& getSingleton();
  ID generateID();

private:
  SIDGenerator();

private:
  ID _idGenerator;
};
