#include "Commands.hpp"

namespace lel::ecs::component
{
  namespace details
  {
    BaseCommands::BaseCommands(const std::unordered_map<Key, Fct>& fcts)
      : _functions{fcts}
    {}
  } /* !details */
} /* !lel::ecs::component */
