#pragma once

#include "C/CRTPC.hpp"
#include "Utility/Vector/Vector.hh"
#include <vector>

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      namespace templateComponent
      {
        template <class Color>
        struct Polygon : public CRTPC<Polygon<Color>>, public Color
        {
        public:
          template <typename ... Args>
          Polygon(Args&& ... args)
            : CRTPC<Polygon<Color>>{}
            , Color{std::forward<Args>(args)...}
          {}
          virtual ~Polygon() = default;

          std::vector<Vector2> points;
        };
      } /* !templateComponent */
    } /* !component */
  } /* !ecs */
} /* !lel */
