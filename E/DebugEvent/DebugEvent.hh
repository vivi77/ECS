#pragma once

#include "E/IE.hh"
#include "E/DebugEvent/debugevent_export.h"
#include <string>

namespace lel::ecs::event
{
  class DEBUGEVENT_EXPORT DebugEvent : public IE
  {
  public:
    DebugEvent(const std::string& msg);
    virtual ~DebugEvent() = default;

    std::string getMessage() const;
    ID getID() const override;

    static ID getEventID();
    static void assignID(const ID);

  private:
    static ID _id;

  private:
    std::string _msg;
  };
} /* !lel::ecs::event */
