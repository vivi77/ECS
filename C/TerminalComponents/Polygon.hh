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

  using TerminalPolygon = templateComponent::Polygon<Vector2<int>, TerminalColor, details::PolyInfo>;
}
