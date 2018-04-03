#include "CLI.hh"
#include "E/CoreEvent/CoreEvent.hh"
#include "E/EManager.hh"
#include "E/CLISystemEvent/CLISystemEvent.hh"
#include <experimental/source_location>

namespace lel::ecs::system
{
  CLI::CLI()
    : _cliparser{}
    , _cmds{
      {
        "quit",
        [](const lel::CmdOutput&) -> void
        {
          lel::ecs::event::EManager::fire<event::CoreEvent>(event::CoreEvent::Type::EXIT);
        }
      },
      {
        "add",
        [](const lel::CmdOutput& o) -> void
        {
          if (o.getArgs().size() != 1)
          {
            std::cout << "Usage: add <system path>\n";
            return ;
          }

          auto sysPath = o.getArgs()[0]->getTerminal();
          lel::ecs::event::EManager::fire<event::CoreEvent>(event::CoreEvent::Type::ADD_SYSTEM, sysPath);
        }
      },
      {
        "remove",
        [](const lel::CmdOutput& o) -> void
        {
          if (o.getArgs().size() != 1)
          {
            std::cout << "Usage: remove <system path>\n";
            return ;
          }

          auto sysPath = o.getArgs()[0]->getTerminal();
          lel::ecs::event::EManager::fire<event::CoreEvent>(event::CoreEvent::Type::REM_SYSTEM, sysPath);
        }
      },
    } //CLI::_cmds end of initialization
    , _enabled{true}
  {}

  void CLI::exec()
  {
    if (!_enabled)
      return ;

    try
    {
      auto expr = _cliparser.parseExpression();
      _cliparser.consume({lel::CLIProducerType::EOL, lel::CLIProducerType::CTRL_D});

      if (expr->getType() != lel::CLIParserType::COMMAND)
      {
        if (expr->getType() == lel::CLIParserType::CANCEL)
        {
          std::cout << "quit\n";
          lel::ecs::event::EManager::fire<event::CoreEvent>(event::CoreEvent::Type::EXIT);
        }
        else if (expr->getType() != lel::CLIParserType::EOL)
          std::cout << "This is not a command. (Type: " << expr->getType() << ")\n";
        return ;
      }

      auto cmd = std::static_pointer_cast<lel::CmdOutput>(expr);
      _cmds.exec(*cmd);
    }
    catch (const std::exception& e)
    {
      std::cerr << std::experimental::source_location::current().function_name()
        << ": " << e.what() << "\n";
      _cliparser.reset();
      return ;
    }
  }

  void CLI::registerEntity(const EntityPtr&)
  {}

  void CLI::setup()
  {}

  void CLI::atRemove()
  {}

  void CLI::update(const EPtr& ptr)
  {
    if (ptr->getID() == event::CLISystemEvent::getEventID())
    {
      auto ev = std::static_pointer_cast<event::CLISystemEvent>(ptr);
      switch (ev->getType())
      {
        case event::CLISystemEvent::Type::DISABLE:
          _enabled = false;
          break;
        case event::CLISystemEvent::Type::ENABLE:
          _enabled = true;
          break;
        default: break;
      }
    }
  }
} /* !lel::ecs::system */
