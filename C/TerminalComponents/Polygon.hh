#pragma once

#include "C/TerminalComponents/terminalcomponents_export.h"
#include "C/TemplateComp/Polygon.hpp"
#include "TerminalColor.hh"

namespace lel::ecs::component
{
  namespace details
  {
    struct PolyInfo
    {
      constexpr static std::string_view name = "TerminalPolygon";
    };
  }

  struct TERMINALCOMPONENTS_EXPORT TerminalPolygon :
    public templateComponent::Polygon<Vector2<int>, TerminalColor, details::PolyInfo>
  {
  public:
    template <typename ... Args>
    TerminalPolygon(const std::vector<Vector2<int>>& points, Args&& ... args)
      : Polygon{points, std::forward<Args>(args)...}
    {}
    virtual ~TerminalPolygon() = default;
  };
} /* !lel */
