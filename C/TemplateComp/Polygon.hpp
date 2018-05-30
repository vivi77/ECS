#pragma once

#include "DefaultInfo.hh"
#include "C/CRTPC.hpp"
#include "Utility/Vector.hpp"
#include <vector>

namespace lel::ecs::component::templateComponent
{
  template <class V, class C, class I = details::DefaultInfo>
  struct Polygon : public CRTPC<Polygon<V, C, I>>, public C, public I
  {
  public:
    using Color = C;
    using Vector = V;

  public:
    template <typename ... Args>
    Polygon(const std::vector<Vector>& pts, Args&& ... args)
      : CRTPC<Polygon<Vector, Color, I>>{}
      , Color{std::forward<Args>(args)...}
      , points{pts}
    {}
    ~Polygon() override = default;

    std::vector<Vector> points;
  };
} /* !lel::ecs::component::templateComponent */
