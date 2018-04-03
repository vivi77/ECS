#pragma once

#include "sidgen_export.h"

namespace lel::ecs::system
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
} /* !lel::ecs::system */
