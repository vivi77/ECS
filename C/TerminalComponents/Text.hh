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

  // TODO: Look for __decltype with type-alias
  struct TERMINALCOMPONENTS_EXPORT TerminalText :
    public templateComponent::Text<TerminalColor, details::TextInfo>
  {
  public:
    template <typename ... Args>
    TerminalText(const char* text, Args&& ... args)
      : Text{text, std::forward<Args>(args)...}
    {}
  };
} /* !lel::ecs::component */
