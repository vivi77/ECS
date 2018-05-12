#pragma once

#include "Parser.hpp"
#include "CLIProducer.hh"
#include <iostream>

namespace lel
{
  enum class CLIParserType { ASSIGN, COMMAND, TERMINAL, OPTION, EOL, CANCEL };
  enum class CLIParserPrecedence { EXPR, COMMAND, ASSIGN, TERMINAL };

  class CLIParserOutput
  {
  public:
    using Type = CLIParserType;

  public:
    CLIParserOutput(const Type type);
    virtual ~CLIParserOutput() = default;
    virtual void dump(std::ostream& = std::cout) const = 0;

    Type getType() const;

  private:
    Type _type;
  };

  struct CLIParserOutPolicy
  {
    using OutputClass = CLIParserOutput;
    using Output = std::shared_ptr<OutputClass>;
    using Precedence = CLIParserPrecedence;

    static Precedence getDefaultPrecedence();
  };

  class CLIParser : public Parser<CLIProducer, CLIParserOutPolicy>
  {
  public:
    CLIParser();

    IP& getProducer();

  private:
    IP _p;
  };
} /* !lel */

std::ostream& operator<<(std::ostream& s, const lel::CLIParserType& t);
