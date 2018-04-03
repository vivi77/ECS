#pragma once

#include "C/TerminalComponents/terminalcomponents_export.h"
#include "C/CRTPC.hpp"
#include "C/TemplateComp/Polygon.hpp"
#include "TerminalColor.hh"

namespace lel::ecs::component
{
  struct TERMINALCOMPONENTS_EXPORT TerminalPolygon :
    public templateComponent::Polygon<Vector2<int>, TerminalColor>
  {
  public:
    template <typename ... Args>
    TerminalPolygon(const std::vector<Vector2<int>>& points, Args&& ... args)
      : Polygon{points, std::forward<Args>(args)...}
    {}
    virtual ~TerminalPolygon() = default;
  };
} /* !lel */
