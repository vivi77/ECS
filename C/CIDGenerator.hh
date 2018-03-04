#pragma once

#include "cidgen_export.h"

class CIDGEN_EXPORT CIDGenerator
{
  using ID = unsigned;

public:
  static CIDGenerator& getSingleton();
  ID generateID();

private:
  CIDGenerator();

private:
  ID _idGenerator;
};
