#pragma once

#include "C/TerminalComponents/terminalcomponents_export.h"
#include "C/CRTPC.hpp"
#include "C/TemplateComp/Text.hpp"
#include "TerminalColor.hh"

namespace lel::ecs::component
{
  // Should use type-alias but there cannot export the class
  struct TERMINALCOMPONENTS_EXPORT TerminalText :
    public templateComponent::Text<TerminalColor>
  {
  public:
    template <typename ... Args>
    TerminalText(const char* text, Args&& ... args)
      : Text{text, std::forward<Args>(args)...}
    {}
  };
} /* !lel::ecs::component */
