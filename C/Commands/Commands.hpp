#pragma once

#include "C/CRTPC.hpp"
#include <unordered_map>

namespace lel::ecs::component
{
  namespace details
  {
    class BaseCommands
    {
    public:
      using Key = std::string;
      using Fct = std::function<void()>;

    public:
      BaseCommands(const std::unordered_map<Key, Fct>& fcts);

      void executeCommand(const Key& key);

    // Could be useful for future usage
    protected:
      std::unordered_map<Key, Fct>& getFunctions()
      {
        return _functions;
      }

    private:
      std::unordered_map<Key, Fct> _functions;
    };
  } /* !details */

  namespace meta
  {
    template <class CommandsID>
    class Commands : public details::BaseCommands, public CRTPC<Commands<CommandsID>>
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

      CommandsID getCommandsOwnerID() const
      {
        return _commandsOwnerId;
      }

    private:
      CommandsID _commandsOwnerId;
    };
  } /* !lel::ecs::meta */

  class CommandsStr : public meta::Commands<std::string>
  {
    using CommandsID = std::string;

  public:
    CommandsStr(const CommandsID& commandsOwnerId,
                const std::unordered_map<Key, Fct>& fcts)
      : Commands{commandsOwnerId, fcts}
    {}

    CommandsStr(const entity::IDEntity& entityOwnerID,
                const CommandsID& commandsOwnerId,
                const std::unordered_map<Key, Fct>& fcts)
      : Commands{entityOwnerID, commandsOwnerId, fcts}
    {}

    ~CommandsStr() override = default;
  };
} /* !lel::ecs::component */
