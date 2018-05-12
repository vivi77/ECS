#include "CoreCommands.hh"
#include "E/CoreCommandsEvent/CoreCommandsEvent.hh"
#include "CLIParser/CLIParserOutputs.hh"
#include <experimental/source_location>
#include <functional>

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
        {
          std::cout << "Usage: add <system path>\n";
          return ;
        }

        auto sysPath = o.getArgs()[0]->getTerminal();
        proxy.addSystem(sysPath);
      }
    },
    {
      "remove",
      [](const lel::CmdOutput& o, lel::ecs::CoreProxy& proxy) -> void
      {
        if (o.getArgs().size() != 1)
        {
          std::cout << "Usage: remove <system path>\n";
          return ;
        }

        auto sysPath = o.getArgs()[0]->getTerminal();
        proxy.removeSystem(sysPath);
      }
    },
    {
      "help",
      [](const auto&, auto&) -> void
      {
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
    const auto evID = ev->getID();
    if (evID == event::CoreCommandsEvent::getEventID())
    {
      const auto event = std::static_pointer_cast<event::CoreCommandsEvent>(ev);
      basicParsing(event->getInput());
    }
  }

  void CoreCommands::basicParsing(const std::string& input)
  {
    try
    {
      _parser.getProducer().feed(input);
      const auto expr = _parser.parseExpression();

      // Maybe useless or too much
      _parser.consume({lel::CLIProducerType::EOL, lel::CLIProducerType::CTRL_D});

      const auto exprType = expr->getType();
      if (exprType != lel::CLIParserType::COMMAND)
      {
        if (exprType == lel::CLIParserType::CANCEL)
        {
          std::cout << "quit\n";
          getProxy().stopCore();
        }
        else if (exprType != lel::CLIParserType::EOL)
          std::cout << "This is not a command. (Type: " << exprType << ")\n";
        return ;
      }

      const auto cmd = std::static_pointer_cast<lel::CmdOutput>(expr);
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
