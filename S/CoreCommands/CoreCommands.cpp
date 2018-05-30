#include "CoreCommands.hh"
#include "E/CoreCommandsEvent/CoreCommandsEvent.hh"
#include "E/TextInputUpdaterEvents/TextInputUpdaterEventsOut.hpp"
#include "CLIParser/CLIParserOutputs.hh"
#include <experimental/source_location>
#include <functional>

ECS_CREATE_IDSYSTEM(CoreCommands)

namespace
{
  const std::unordered_map<
    std::string,
    std::function<void (const lel::CmdOutput&, lel::ecs::CoreProxy&)>>
  CORE_COMMANDS
  {
    {
      "quit",
      [](const lel::CmdOutput&, lel::ecs::CoreProxy& proxy) -> void
      {
        proxy.stopCore();
      }
    },
    {
      "add",
      [](const lel::CmdOutput& o, lel::ecs::CoreProxy& proxy) -> void
      {
        if (o.getArgs().size() != 1)
          std::cout << "Usage: add <system path>\n";
        else
          proxy.addSystem(o.getArgs()[0]->getTerminal());
      }
    },
    {
      "remove",
      [](const lel::CmdOutput& o, lel::ecs::CoreProxy& proxy) -> void
      {
        if (o.getArgs().size() != 1)
          std::cout << "Usage: remove <system path>\n";
        else
          proxy.removeSystem(o.getArgs()[0]->getTerminal());
      }
    },
    {
      "reload",
      [](const lel::CmdOutput& o, lel::ecs::CoreProxy& proxy) -> void
      {
        if (o.getArgs().size() != 1)
          std::cout << "Usage: reload <system path>\n";
        else
          proxy.reloadSystem(o.getArgs()[0]->getTerminal());
      }
    },
    {
      "help",
      [](const auto&, auto&) -> void
      {
        // Maybe send an event back ?
        std::cout << "Available commands are:\n"
          << "\tquit: Exit the program\n"
          << "\tadd <system> [system ...]: Add one or more systems\n"
          << "\tremove <system> [system ...]: Remove one or more systems\n";
      }
    },
  };
} /* ! */

namespace lel::ecs::system
{
  CoreCommands::CoreCommands(CoreProxy& proxy)
    : CRTPS{proxy}
  {}

  void CoreCommands::exec()
  {}

  void CoreCommands::registerEntity(const EntityPtr&)
  {}

  void CoreCommands::deregisterEntity(const EntityPtr&)
  {}

  void CoreCommands::setup()
  {}

  void CoreCommands::atRemove()
  {}

  void CoreCommands::update(const EPtr& ev)
  {
    using CCE = event::CoreCommandsEvent;
    using TIUEOStr = event::TextInputUpdaterEventsOut<std::string>;

    const auto evID = ev->getID();
    if (evID == CCE::getEventID())
    {
      const auto event = std::static_pointer_cast<CCE>(ev);
      switch (event->getType())
      {
        case event::CoreCommandsEvent::Type::CTRL_D:
          getProxy().stopCore();
          break;
        case event::CoreCommandsEvent::Type::INPUT:
          basicParsing(event->getInput());
          break;
      }
    }
    else if (evID == TIUEOStr::getEventID())
    {
      const auto event = std::static_pointer_cast<TIUEOStr>(ev);
      basicParsing(event->getInput());
    }
  }

  // Input format anything without '\n'
  // Unknown behavior if this is not respected
  // TODO: Maybe need to change the producer of CLIParser ??
  void CoreCommands::basicParsing(const std::string& input)
  {
    try
    {
      _parser.getProducer().feed(input);
      const auto expr = _parser.parseExpression();

      // Maybe useless or too much
      _parser.consume({CLIProducerType::EOL, CLIProducerType::CTRL_D});

      const auto exprType = expr->getType();
      if (exprType != CLIParserType::COMMAND && exprType != CLIParserType::EOL)
      {
        std::cout << "This is not a command. (Type: " << exprType << ")\n";
        return ;
      }

      const auto cmd = std::static_pointer_cast<CmdOutput>(expr);
      const auto it = CORE_COMMANDS.find(cmd->getCommand());
      if (it == std::end(CORE_COMMANDS))
        std::cout << "Unknown command '" << cmd->getCommand() << "'\n";
      else
        it->second(*cmd, getProxy());
    }
    catch (const std::exception& e)
    {
      std::cerr << std::experimental::source_location::current().function_name()
        << ": " << e.what() << "\n";
      _parser.reset();
    }
  }
} /* !lel::ecs::system */
