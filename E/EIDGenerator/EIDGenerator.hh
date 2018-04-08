#pragma once

#include "E/EIDGenerator/eidgen_export.h"
#include "Utility/IIDGenerator.hpp"
#include "Utility/Fwd.hh"

namespace lel::ecs::event
{
  class EIDGEN_EXPORT EIDGenerator : public utility::IIDGenerator<IDEvent>
  {
  public:
    using ID = IDEvent;

  public:
    virtual ~EIDGenerator() = default;
    ID generateID() override;

  private:
    ID _id = 1; // Not 0 because it is reserved for DebugEvent
  };

  namespace old
  {
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
  } /* !old */
} /* !lel::ecs::event */
