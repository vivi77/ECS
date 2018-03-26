#pragma once

#include "CLIParser.hh"
#include <memory>
#include <vector>

namespace lel
{
  template <class T, typename ... Args>
  std::unique_ptr<T> createCLIParserOutput(Args&& ... args)
  {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }

  class TerminalOutput : public CLIParserOutput
  {
  public:
    TerminalOutput(const std::string& s);
    virtual ~TerminalOutput() = default;
    void dump(std::ostream&) const override;

    std::string getTerminal() const;

  private:
    std::string _s;
  };

  class OptionOutput : public CLIParserOutput
  {
  public:
    OptionOutput(const CLIParser::Output& o);
    virtual ~OptionOutput() = default;
    void dump(std::ostream&) const override;

  private:
    CLIParser::Output _o;
  };

  class AssignOutput : public CLIParserOutput
  {
  public:
    AssignOutput(const CLIParser::Output& left, const CLIParser::Output& right);
    virtual ~AssignOutput() = default;
    void dump(std::ostream&) const override;

  private:
    CLIParser::Output _left;
    CLIParser::Output _right;
  };

  class CmdOutput : public CLIParserOutput
  {
  public:
    CmdOutput(const std::shared_ptr<TerminalOutput>& cmd,
              const std::vector<std::shared_ptr<TerminalOutput>>& args,
              const std::vector<std::shared_ptr<OptionOutput>>& opts);
    virtual ~CmdOutput() = default;
    void dump(std::ostream&) const override;

    std::string getCommand() const;
    std::vector<std::shared_ptr<TerminalOutput>> getArgs() const;
    std::vector<std::shared_ptr<OptionOutput>> getOpts() const;

  private:
    std::shared_ptr<TerminalOutput> _cmd;
    std::vector<std::shared_ptr<TerminalOutput>> _args;
    std::vector<std::shared_ptr<OptionOutput>> _opts;
  };

  class CmdOutputBuilder
  {
    using ArgContainer = std::vector<std::shared_ptr<TerminalOutput>>;
    using OptContainer = std::vector<std::shared_ptr<OptionOutput>>;

  public:
    void setCmd(const std::shared_ptr<TerminalOutput>& cmd);
    void addArg(const std::shared_ptr<TerminalOutput>& arg);
    void addOpt(const std::shared_ptr<OptionOutput>& opt);
    CmdOutputBuilder& clear();
    std::shared_ptr<CmdOutput> build();

  private:
    std::shared_ptr<TerminalOutput> _cmd;
    ArgContainer _args;
    OptContainer _opts;
  };

  class EOLOutput : public CLIParserOutput
  {
  public:
    EOLOutput();
    virtual ~EOLOutput() = default;
    void dump(std::ostream&) const override;
  };

  class CancelOutput : public CLIParserOutput
  {
  public:
    CancelOutput();
    virtual ~CancelOutput() = default;
    void dump(std::ostream&) const override;
  };
} /* !lel */
