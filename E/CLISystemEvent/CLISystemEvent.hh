#pragma once

#include "CRTPE.hpp"
#include "E/CLISystemEvent/clisystemevent_export.h"

class CLISYSTEMEVENT_EXPORT CLISystemEvent : public CRTPE<CLISystemEvent>
{
public:
  enum class Type : char
  {
    UNKNOWN,

    //Commands
    DISABLE,
    ENABLE,
  };

public:
  CLISystemEvent(Type t = Type::UNKNOWN);
  virtual ~CLISystemEvent() = default;

  Type getType() const;

private:
  Type _t;
};
