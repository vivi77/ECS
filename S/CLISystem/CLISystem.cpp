#include "CLISystem.hh"
#include "CoreEvent.hh"
#include "EManager.hh"
#include <iostream>

CLISystem::Tokenizer::Tokenizer(const std::string& line)
  : _line{line}
{
  tokenize();
}

void CLISystem::Tokenizer::tokenize()
{
  unsigned i = 0;
  const auto lineSize = _line.size();

  while (i < lineSize)
  {
    if (isBlank(_line[i]))
    {
      ++i;
      while (isBlank(_line[i]))
        ++i;
    }
    else
    {
      const auto start = i;
      ++i;
      while (!isBlank(_line[i]))
        ++i;
      auto token = _line.substr(start, i - start);
      _tokens.emplace(token, Type::STRING);
    }
  }
  _tokens.emplace("", Type::END);
}

CLISystem::Tokenizer::Token CLISystem::Tokenizer::consume(const Type t)
{
  auto token = _tokens.front();
  if (token.second != t)
    std::runtime_error{"Invalid token"};
  _tokens.pop();
  return token;
}

bool CLISystem::Tokenizer::isBlank(const char c)
{
  return c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\r' || c == '\f';
}

void CLISystem::exec()
{
  std::string input;
  if (!std::getline(std::cin, input))
    EManager::fire(std::make_shared<CoreEvent>(CoreEvent::Type::EXIT));
  else
  {
    Tokenizer tokenizer{input};
    try
    {
      auto cmd = tokenizer.consume(Tokenizer::Type::STRING);
      if (cmd.first == "add")
      {
        auto arg1 = tokenizer.consume(Tokenizer::Type::STRING);
        EManager::fire(std::make_shared<CoreEvent>(CoreEvent::Type::ADD_SYSTEM, arg1.first));
      }
      else if (cmd.first == "remove")
      {
        auto arg1 = tokenizer.consume(Tokenizer::Type::STRING);
        EManager::fire(std::make_shared<CoreEvent>(CoreEvent::Type::REM_SYSTEM, arg1.first));
      }
      else if (cmd.first == "help")
      {
        std::cout << "Command available:\n"
          << "add <system>\n" << "remove <system>\n" << "exit|quit\n";
      }
      else if (cmd.first == "exit" || cmd.first == "quit")
      {
        EManager::fire(std::make_shared<CoreEvent>(CoreEvent::Type::EXIT));
      }
      else
        std::cerr << "Unknown command '" << cmd.first << "'\n";
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
    }
  }
}
