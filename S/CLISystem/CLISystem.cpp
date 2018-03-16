#include "CLISystem.hh"
#include "CoreEvent.hh"
#include "EManager.hh"
#include "parsing/CLIParserOutputs.hh"

CLISystem::CLISystem()
  : cliproducer{}
  , cliparser{cliproducer}
{}

void CLISystem::exec()
{
  auto expr = cliparser.parseExpression();
  if (expr->getType() != lel::CLIParserType::COMMAND)
  {
    std::cout << "This is not a command\n";
    return ;
  }
  auto cmd = std::static_pointer_cast<lel::CmdOutput>(expr);
  if (cmd->getCommand() == "quit")
    EManager::fire<CoreEvent>(CoreEvent::Type::EXIT);
  else
    std::cout << "Unknown command '" << cmd->getCommand() << "'\n";
  cliparser.consume(lel::CLIProducerType::EOL);
}
