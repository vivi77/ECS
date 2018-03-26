#pragma once

#include "CLIParser.hh"

namespace lel
{
  class CommandParselet : public CLIParser::IPrefixParselet
  {
  public:
    virtual ~CommandParselet() = default;
    CLIParser::Output parse(CLIParser::Parser&, const CLIParser::Input& i) override;
  };

  class OptionParselet : public CLIParser::IPrefixParselet
  {
  public:
    virtual ~OptionParselet() = default;
    CLIParser::Output parse(CLIParser::Parser&, const CLIParser::Input& i) override;
  };

  class InfixAssignParselet : public CLIParser::IInfixParselet
  {
  public:
    virtual ~InfixAssignParselet() = default;
    CLIParser::Output parse(CLIParser::Parser&, const CLIParser::Output&, const CLIParser::Input&) override;
    CLIParser::Precedence getPrecedence() const override;
  };

  class InfixCmdArgParselet : public CLIParser::IInfixParselet
  {
  public:
    virtual ~InfixCmdArgParselet() = default;
    CLIParser::Output parse(CLIParser::Parser&, const CLIParser::Output&, const CLIParser::Input&) override;
    CLIParser::Precedence getPrecedence() const override;
  };

  class EOLParselet : public CLIParser::IPrefixParselet
  {
  public:
    virtual ~EOLParselet() = default;
    CLIParser::Output parse(CLIParser::Parser&, const CLIParser::Input&) override;
  };

  class CancelParselet : public CLIParser::IPrefixParselet
  {
  public:
    virtual ~CancelParselet() = default;
    CLIParser::Output parse(CLIParser::Parser&, const CLIParser::Input&) override;
  };

  //class InfixSimpleCmdParselet : public CLIParser::IInfixParselet
  //{
  //public:
    //virtual ~InfixSimpleCmdParselet() = default;
    //CLIParser::Output parse(CLIParser::Parser&, const CLIParser::Output&, const CLIParser::Input&) override;
    //CLIParser::Precedence getPrecedence() const override;
  //};
} /* !lel */
