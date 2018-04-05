#pragma once

#include "E/CRTPE.hpp"
#include "E/DebugEvent/debugevent_export.h"
#include <string>

namespace lel::ecs::event
{
  class DEBUGEVENT_EXPORT DebugEvent : public CRTPE<DebugEvent>
  {
  public:
    DebugEvent(const std::string& msg);

    std::string getMessage() const;

  private:
    std::string _msg;
  };
} /* !lel::ecs::event */
