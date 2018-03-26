#include "CLIParserParselets.hh"
#include "CLIParserOutputs.hh"
#include <vector>
#include <optional>

namespace lel
{
  CLIParser::Output CommandParselet::parse(CLIParser::Parser&, const CLIParser::Input& i)
  {
    CmdOutputBuilder builder;
    builder.setCmd(createCLIParserOutput<TerminalOutput>(i.getOutput()));
    return builder.build();
  }

  CLIParser::Output OptionParselet::parse(CLIParser::Parser& parser, const CLIParser::Input&)
  {
    auto expr = parser.parseExpression(CLIParserPrecedence::COMMAND); //ASSIGN + 1 == COMMAND
    if (expr->getType() == CLIParserType::COMMAND)
    {
      auto cmd = std::static_pointer_cast<CmdOutput>(expr)->getCommand();
      return createCLIParserOutput<OptionOutput>(createCLIParserOutput<TerminalOutput>(cmd));
    }
    return createCLIParserOutput<OptionOutput>(expr);
  }

  CLIParser::Output InfixAssignParselet::parse(CLIParser::Parser& p, const CLIParser::Output& o, const CLIParser::Input&)
  {
    if (o->getType() != CLIParserType::COMMAND)
      return o;

    auto castO = std::static_pointer_cast<CmdOutput>(o);
    std::shared_ptr<TerminalOutput> left = createCLIParserOutput<TerminalOutput>(castO->getCommand());

    auto expr = std::static_pointer_cast<CmdOutput>(p.parseExpression(getPrecedence()));
    std::shared_ptr<TerminalOutput> right = createCLIParserOutput<TerminalOutput>(expr->getCommand());

    return createCLIParserOutput<AssignOutput>(left, right);
  }

  CLIParser::Precedence InfixAssignParselet::getPrecedence() const
  {
    return CLIParser::Precedence::ASSIGN;
  }

  CLIParser::Output InfixCmdArgParselet::parse(CLIParser::Parser& p, const CLIParser::Output& o, const CLIParser::Input& i)
  {
    if (o->getType() != CLIParserType::COMMAND)
      return o;

    std::shared_ptr<CmdOutput> castO = std::static_pointer_cast<CmdOutput>(o);
    CmdOutputBuilder builder;
    builder.setCmd(createCLIParserOutput<TerminalOutput>(castO->getCommand()));
    CLIProducerType t = i.getType();

    switch (t)
    {
      case CLIProducerType::STRING:
        {
          t = p.lookAhead(0).getType();
          std::shared_ptr<TerminalOutput> output = createCLIParserOutput<TerminalOutput>(i.getOutput());
          if (t == CLIProducerType::EQUAL)
          {
            auto expr = std::static_pointer_cast<CmdOutput>(p.parseExpression(CLIParserPrecedence::TERMINAL));
            std::shared_ptr<TerminalOutput> right = createCLIParserOutput<TerminalOutput>(expr->getCommand());
            std::shared_ptr<AssignOutput> assign = createCLIParserOutput<AssignOutput>(output, right);
            builder.addOpt(createCLIParserOutput<OptionOutput>(assign));
          }
          else
            builder.addArg(output);
          break;
        }
      case CLIProducerType::DASH:
        {
          auto opt = p.parseExpression(CLIParserPrecedence::COMMAND);
          builder.addOpt(createCLIParserOutput<OptionOutput>(opt));
          break;
        }
      default:
        return builder.build();
    }

    CLIParser::Output expr;

    for (;;)
    {
      t = p.lookAhead(0).getType();
      if (t != CLIProducerType::STRING && t != CLIProducerType::DASH)
        return builder.build();

      expr = p.parseExpression(getPrecedence());

      switch (t)
      {
        case CLIProducerType::STRING:
          {
            auto cmd = std::static_pointer_cast<CmdOutput>(expr);
            builder.addArg(createCLIParserOutput<TerminalOutput>(cmd->getCommand()));
            break;
          }
        case CLIProducerType::DASH:
          builder.addOpt(std::static_pointer_cast<OptionOutput>(expr));
          break;
        default:
          return builder.build();
      }
    }
  }

  CLIParser::Precedence InfixCmdArgParselet::getPrecedence() const
  {
    return CLIParser::Precedence::COMMAND;
  }

  CLIParser::Output EOLParselet::parse(CLIParser::Parser&, const CLIParser::Input&)
  {
    return createCLIParserOutput<EOLOutput>();
  }

  CLIParser::Output CancelParselet::parse(CLIParser::Parser&, const CLIParser::Input&)
  {
    return createCLIParserOutput<CancelOutput>();
  }

  //CLIParser::Output InfixSimpleCmdParselet::parse(CLIParser::Parser& p, const CLIParser::Output& o, const CLIParser::Input&)
  //{
    //CmdOutputBuilder builder;
    //builder.setCmd(std::static_pointer_cast<TerminalOutput>(o));
    //return builder.build();
  //}

  //CLIParser::Precedence InfixSimpleCmdParselet::getPrecedence() const
  //{
    //return CLIParserPrecedence::TERMINAL;
  //}
} /* !lel */

#if 0
syntax = expression
expression = command
command = string suffixlist EOL
suffixlist = EMPTY | suffixlist suffix
suffix = string | option
option = string '=' string
#endif
