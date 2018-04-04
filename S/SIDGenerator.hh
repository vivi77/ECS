#pragma once

#include "S/sidgen_export.h"
#include "Utility/IIDGenerator.hpp"

namespace lel::ecs::system
{
  class SIDGEN_EXPORT SIDGenerator : public utility::IIDGenerator<IDSystem>
  {
  public:
    IDSystem generateID();

  private:
    IDSystem _id;
  };

  namespace old
  {
    // TODO: Rethink this.
    //   Solution proposition:
    //    1) Use of interface + abstract class between IS and CRTPS
    class SIDGEN_EXPORT SIDGenerator
    {
      using ID = unsigned;

    public:
      static SIDGenerator& getSingleton();
      ID generateID();

    private:
      SIDGenerator();

    private:
      ID _idGenerator;
    };
  } /* !old */
} /* !lel::ecs::system */
