#pragma once

#include "C/cidgen_export.h"

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      class CIDGEN_EXPORT CIDGenerator
      {
        using ID = unsigned;

      public:
        static CIDGenerator& getSingleton();
        ID generateID();

      private:
        CIDGenerator();

      private:
        ID _idGenerator;
      };
    } /* !component */
  } /* !ecs */
} /* !lel */
