#pragma once

#include "CRTPS.hpp"
#include <queue>
#include <string>

class CLISystem : public CRTPS<CLISystem>
{
  class Tokenizer
  {
  public:
    enum class Type
    {
      END,
      STRING,
      //OPTION, //May be implemented. One day...
    };

  public:
    using Token = std::pair<std::string, Type>;

  public:
    Tokenizer(const std::string&);
    void tokenize();
    Token consume(const Type);

  private:
    static bool isBlank(const char c);

  private:
    std::string _line;
    std::queue<Token> _tokens;
  };

public:
  virtual ~CLISystem() = default;
  void exec() override;
};
