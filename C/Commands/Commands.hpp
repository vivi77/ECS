#pragma once

#include "C/CRTPC.hpp"
#include <unordered_map>

namespace lel::ecs::component
{
  namespace details
  {
    class BaseCommands : public CRTPC<BaseCommands>
    {
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

  template <class CommandsID>
  class Commands : public details::BaseCommands
  {
  public:
    Commands(const CommandsID& id)
      : _id{id}
    {}

    ~Commands() override = default;

    CommandsID getCommandsID() const
    {
      return _id;
    }

  private:
    CommandsID _id;
  };
} /* !lel::ecs::component */
