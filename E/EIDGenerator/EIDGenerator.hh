#pragma once

#include "E/IE.hh"
#include "E/IDEvent.hh"
#include "E/EIDGenerator/eidgen_export.h"
#include "Utility/IIDGenerator.hpp"

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
      ~DebugEvent() override = default;

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
    ID _id{0};
  };
} /* !lel::ecs::event */
