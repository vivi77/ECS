#pragma once

#include "E/EIDGenerator/eidgen_export.h"
#include "Utility/IIDGenerator.hpp"
#include "Utility/Fwd.hh"

namespace lel::ecs::event
{
  class DebugEvent;

  // TODO: DebugEvent could become BasicEvent, a nested class of EIDGenerator.
  // ==> Problem: having DebugEvent being a 'friend' class
  class EIDGEN_EXPORT EIDGenerator : public utility::IIDGenerator<IDEvent>
  {
  public:
    using ID = IDEvent;

  public:
    virtual ~EIDGenerator() = default;
    ID generateID() override;

  private:
    ID _id = _debugEventID + 1; // Not 0 because it is reserved for DebugEvent

  private:
    static constexpr ID _debugEventID = 0;
    friend DebugEvent;
  };
} /* !lel::ecs::event */
