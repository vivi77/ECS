#pragma once

#include "IE.hh"
#include "IDEvent.hh"
#include "Utility/IIDGenerator.hpp"

namespace lel::ecs::event
{
  // TODO: DebugEvent could become DebugEvent, a nested class of EIDGenerator.
  // ==> Problem: having DebugEvent being a 'friend' class
  class EIDGenerator : public utility::IIDGenerator<IDEvent>
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
