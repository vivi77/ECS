#pragma once

#include "C/CRTPC.hpp"
#include "Utility/Vector.hpp"
#include <vector>

namespace lel::ecs::component::templateComponent
{
  template <class _Vector, class _Color>
  struct Polygon : public CRTPC<Polygon<_Vector, _Color>>, public _Color
  {
  public:
    using Color = _Color;
    using Vector = _Vector;

  public:
    template <typename ... Args>
    Polygon(const std::vector<Vector>& pts, Args&& ... args)
      : CRTPC<Polygon<Vector, Color>>{}
      , Color{std::forward<Args>(args)...}
      , points{pts}
    {}
    virtual ~Polygon() = default;

    std::vector<Vector> points;
  };
} /* !lel::ecs::component::templateComponent */
