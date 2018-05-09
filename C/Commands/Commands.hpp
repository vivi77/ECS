#pragma once

#include "C/CRTPC.hpp"
#include <unordered_map>

namespace lel::ecs::component
{
  namespace details
  {
    struct BaseCommands
    {
      using Key = std::string;
      using Fct = std::function<void()>;

      BaseCommands(const std::unordered_map<Key, Fct>& fcts);

      std::unordered_map<Key, Fct> _functions;
    };
  } /* !details */

  namespace meta
  {
    template <class CommandsID>
    struct Commands : public details::BaseCommands, public CRTPC<Commands<CommandsID>>
    {
    public:
      Commands(const CommandsID& commandsOwnerId,
               const std::unordered_map<Key, Fct>& fcts)
        : BaseCommands{fcts}
        , CRTPC<Commands<CommandsID>>{}
        , _commandsOwnerId{commandsOwnerId}
      {}

      Commands(const entity::IDEntity& entityOwnerID,
               const CommandsID& commandsOwnerId,
               const std::unordered_map<Key, Fct>& fcts)
        : BaseCommands{fcts}
        , CRTPC<Commands<CommandsID>>{entityOwnerID}
        , _commandsOwnerId{commandsOwnerId}
      {}

      ~Commands() override = default;

      CommandsID _commandsOwnerId;
    };
  } /* !lel::ecs::meta */

  using CommandsStr = meta::Commands<std::string>;
} /* !lel::ecs::component */
