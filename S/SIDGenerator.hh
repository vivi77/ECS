#pragma once

#include "sidgen_export.h"

namespace lel
{
  namespace ecs
  {
    namespace system
    {
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
    } /* !system */
  } /* !ecs */
} /* !lel */
