#pragma once

#include "S/CRTPS.hpp"
#include "CLIParser/CLIParser.hh"
#include "CLIParser/CLIParserOutputs.hh"
#include <functional>

// TODO: To move elsewhere
class CmdManager
{
public:
  using Command = std::string;
  using Callback = std::function<void(const lel::CmdOutput&)>;

public:
  CmdManager(std::initializer_list<std::unordered_map<Command, Callback>::value_type> l)
    : _actions{l}
  {}

  void exec(const lel::CmdOutput& output)
  {
    auto it = _actions.find(output.getCommand());
    if (it == std::end(_actions))
      std::cout << "Unknown command '" << output.getCommand() << "'\n";
    else
      it->second(output);
  }

private:
  std::unordered_map<Command, Callback> _actions;
};

namespace lel::ecs::system
{
  class CLI : public CRTPS<CLI>, public event::IEListener
  {
  public:
    CLI();
    virtual ~CLI() = default;
    void exec() override;
    void registerEntity(const EntityPtr&) override;
    void setup() override;
    void atRemove() override;

    void update(const EPtr&) override;

  private:
    CLIParser _cliparser;
    CmdManager _cmds;
    bool _enabled = true;

  public:
    constexpr static std::string_view name{"CLIParser"};
  };
} /* !lel::ecs::system */
