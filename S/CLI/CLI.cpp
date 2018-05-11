#include "CLI.hh"
#include "E/EManager/EManager.hh"
#include "E/CLISystemEvent/CLISystemEvent.hh"
#include <experimental/source_location>

namespace lel::ecs::system
{
  CLI::CLI(CoreProxy& proxy)
    : CRTPS{proxy}
    , _cliparser{}
    , _cmds{
      {
        "quit",
        [this](const CmdOutput&) -> void
        {
          getProxy().stopCore();
        }
      },
      {
        "add",
        [this](const CmdOutput& o) -> void
        {
          if (o.getArgs().size() != 1)
          {
            std::cout << "Usage: add <system path>\n";
            return ;
          }

          auto sysPath = o.getArgs()[0]->getTerminal();
          getProxy().addSystem(sysPath);
        }
      },
      {
        "remove",
        [this](const CmdOutput& o) -> void
        {
          if (o.getArgs().size() != 1)
          {
            std::cout << "Usage: remove <system path>\n";
            return ;
          }

          auto sysPath = o.getArgs()[0]->getTerminal();
          //getProxy()->fire<event::CoreEvent>(event::CoreEvent::Type::REM_SYSTEM, sysPath);
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
      _cliparser.consume({CLIProducerType::EOL, CLIProducerType::CTRL_D});

      if (expr->getType() != CLIParserType::COMMAND)
      {
        if (expr->getType() == CLIParserType::CANCEL)
        {
          std::cout << "quit\n";
          getProxy().stopCore();
        }
        else if (expr->getType() != CLIParserType::EOL)
          std::cout << "This is not a command. (Type: " << expr->getType() << ")\n";
        return ;
      }

      auto cmd = std::static_pointer_cast<CmdOutput>(expr);
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

  void CLI::deregisterEntity(const EntityPtr&)
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
