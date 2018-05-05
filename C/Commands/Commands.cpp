#include "Commands.hpp"

namespace lel::ecs::component
{
  namespace details
  {
    BaseCommands::BaseCommands(const std::unordered_map<Key, Fct>& fcts)
      : CRTPC{}
      , _functions{fcts}
    {}

    BaseCommands::BaseCommands(const entity::IDEntity& entityOwnerID,
                               const std::unordered_map<Key, Fct>& fcts)
      : CRTPC{entityOwnerID}
      , _functions{fcts}
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
