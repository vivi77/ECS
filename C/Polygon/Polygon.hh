#pragma once

#include "C/Polygon/polygon_export.h"
#include "C/CRTPC.hpp"
#include "Utility/Vector/Vector.hh"
#include <vector>

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      struct POLYGON_EXPORT Polygon : public CRTPC<Polygon>
      {
      public:
        virtual ~Polygon() = default;

        std::vector<Vector2> points;
      };
    } /* !component */
  } /* !ecs */
} /* !lel */
