#include "CLISystem.hh"
#include "E/CoreEvent/CoreEvent.hh"
#include "E/EManager.hh"
#include "E/CLISystemEvent/CLISystemEvent.hh"
#include <experimental/source_location>

CLISystem::CLISystem()
  : _cliproducer{}
  , _cliparser{_cliproducer}
  , _cmds{
    {
      "quit",
      [](const lel::CmdOutput&) -> void
      {
        EManager::fire<CoreEvent>(CoreEvent::Type::EXIT);
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
        EManager::fire<CoreEvent>(CoreEvent::Type::ADD_SYSTEM, sysPath);
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
        EManager::fire<CoreEvent>(CoreEvent::Type::REM_SYSTEM, sysPath);
      }
    },
  } //CLISystem::_cmds end of initialization
{}

void CLISystem::exec()
{
  try
  {
    auto expr = _cliparser.parseExpression();
    _cliparser.consume({lel::CLIProducerType::EOL, lel::CLIProducerType::CTRL_D});

    if (expr->getType() != lel::CLIParserType::COMMAND)
    {
      if (expr->getType() == lel::CLIParserType::CANCEL)
      {
        std::cout << "quit\n";
        EManager::fire<CoreEvent>(CoreEvent::Type::EXIT);
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

void CLISystem::registerEntity(const EntityPtr&)
{}

void CLISystem::setup()
{}

void CLISystem::atRemove()
{}

void CLISystem::update(const EPtr& ptr)
{
  if (ptr->getID() == CLISystemEvent::getEventID())
  {
    auto ev = std::static_pointer_cast<CLISystemEvent>(ptr);
    switch (ev->getType())
    {
      case CLISystemEvent::Type::DISABLE:
        break;
      case CLISystemEvent::Type::ENABLE:
        break;
      default: break;
    }
  }
}
