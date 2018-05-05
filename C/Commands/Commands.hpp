#pragma once

#include "C/CRTPC.hpp"
#include <unordered_map>

namespace lel::ecs::component
{
  namespace details
  {
    class BaseCommands : public CRTPC<BaseCommands>
    {
    protected:
      using Key = std::string;
      using Fct = std::function<void()>;

    public:
      BaseCommands(const std::unordered_map<Key, Fct>& fcts);
      BaseCommands(const entity::IDEntity& entityOwnerID,
                   const std::unordered_map<Key, Fct>& fcts);

      ~BaseCommands() override = default;

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
    class Commands : public details::BaseCommands
    {
    public:
      Commands(const CommandsID& id,
               const std::unordered_map<Key, Fct>& fcts)
        : BaseCommands{fcts}
        , _id{id}
      {}

      Commands(const entity::IDEntity& entityOwnerID,
               const CommandsID& id,
               const std::unordered_map<Key, Fct>& fcts)
        : BaseCommands{entityOwnerID, fcts}
        , _id{id}
      {}

      ~Commands() override = default;

      CommandsID getCommandsID() const
      {
        return _id;
      }

    private:
      CommandsID _id;
    };
  } /* !lel::ecs::meta */

  class CommandsStr : public meta::Commands<std::string>
  {
    using CommandsID = std::string;

  public:
    CommandsStr(const CommandsID& id,
                const std::unordered_map<Key, Fct>& fcts)
      : Commands{id, fcts}
    {}

    CommandsStr(const entity::IDEntity& entityOwnerID,
                const CommandsID& id,
                const std::unordered_map<Key, Fct>& fcts)
      : Commands{entityOwnerID, id, fcts}
    {}

    ~CommandsStr() override = default;
  };
} /* !lel::ecs::component */
