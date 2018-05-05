#include "Commands.hpp"

namespace lel::ecs::component
{
  namespace details
  {
    BaseCommands::BaseCommands(const std::unordered_map<Key, Fct>& fcts)
      : _functions{fcts}
    {}

    void BaseCommands::executeCommand(const Key& key)
    {
      const auto it = _functions.find(key);
      const auto end = std::end(_functions);
      if (it == end)
        return ;
      it->second();
    }
  } /* !details */
} /* !lel::ecs::component */
