#pragma once

#include "E/eidgen_export.h"

class EIDGEN_EXPORT EIDGenerator
{
public:
  using ID = unsigned;

public:
  static EIDGenerator& getSingleton();
  ID generateID();

private:
  EIDGenerator();

private:
  ID _idGenerator;
};
