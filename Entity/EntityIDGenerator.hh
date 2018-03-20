#pragma once

#include "entitylogic_export.h"

class ENTITYLOGIC_EXPORT EntityIDGenerator
{
public:
  using ID = unsigned;

public:
  static ID generateID();

private:
  static ID _id;
};
