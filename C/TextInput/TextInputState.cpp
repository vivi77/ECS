#include "TextInputState.hh"

namespace lel::ecs::component
{
  TextInputState::TextInputState(const bool active, const bool focused)
    : active{active}
    , focused{focused}
  {}
} /* !lel::ecs::component */
