#pragma once

#include "E/IE.hh"
#include "E/EIDGenerator/eidgen_export.h"
#include "Utility/IIDGenerator.hpp"
#include "Utility/Fwd.hh"

namespace lel::ecs::event
{
  // TODO: DebugEvent could become DebugEvent, a nested class of EIDGenerator.
  // ==> Problem: having DebugEvent being a 'friend' class
  class EIDGEN_EXPORT EIDGenerator : public utility::IIDGenerator<IDEvent>
  {
  public:
    using ID = IDEvent;

  public:
    // This class is here to solve a cyclic dependency problem
    class DebugEvent : public IE
    {
    public:
      DebugEvent(const std::string& msg);
      virtual ~DebugEvent() = default;

      std::string getMessage() const;
      ID getID() const override;

      static ID getEventID();

    private:
      static ID _id;

    private:
      std::string _msg = "";
    };

  public:
    virtual ~EIDGenerator() = default;
    ID generateID() override;

  private:
    ID _id = _debugEventID + 1; // Not 0 because it is reserved for DebugEvent

  private:
    static constexpr ID _debugEventID = 0;
  };
} /* !lel::ecs::event */
