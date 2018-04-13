#pragma once

#include "C/TerminalComponents/terminalcomponents_export.h"
#include "C/CRTPC.hpp"
#include "C/TemplateComp/Text.hpp"
#include "TerminalColor.hh"

namespace lel::ecs::component
{
  namespace details
  {
    struct TextInfo
    {
      constexpr static std::string_view name = "TerminalText";
    };
  } /* !details */

  using TerminalText = templateComponent::Text<TerminalColor, details::TextInfo>;
} /* !lel::ecs::component */
