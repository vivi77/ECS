#pragma once

#include "C/CRTPC.hpp"

namespace lel::ecs::component
{
  struct TextInputState : public CRTPC<TextInputState>
  {
    TextInputState(const bool active, const bool focused);

    bool active = true;
    bool focused = true;
  };
} /* !lel::ecs::component */
