#pragma once

#include "E/CRTPE.hpp"
#include "E/CLISystemEvent/clisystemevent_export.h"

namespace lel::ecs::event
{
  class CLISYSTEMEVENT_EXPORT CLISystemEvent : public CRTPE<CLISystemEvent>
  {
  public:
    enum class Type : char
    {
      //Commands
      DISABLE,
      ENABLE,
    };

  public:
    CLISystemEvent(Type t);
    ~CLISystemEvent() override = default;

    Type getType() const;

  private:
    Type _t;
  };
} /* !lel::ecs::event */
