#include "CLIParserOutputs.hh"

namespace lel
{
  TerminalOutput::TerminalOutput(const std::string& s)
    : CLIParserOutput{CLIParserType::TERMINAL}
    , _s{s}
  {}

  void TerminalOutput::dump(std::ostream& s) const
  {
    s << "\033[33m(\033[0m" << _s << "\033[33m)\033[0m";
  }

  std::string TerminalOutput::getTerminal() const
  {
    return _s;
  }

  OptionOutput::OptionOutput(const CLIParser::Output& o)
    : CLIParserOutput{CLIParserType::OPTION}
    , _o{o}
  {}

  void OptionOutput::dump(std::ostream& s) const
  {
    s << "\033[31m(-\033[0m";
    _o->dump(s);
    s << "\033[31m)\033[0m";
  }

  AssignOutput::AssignOutput(const CLIParser::Output& left, const CLIParser::Output& right)
    : CLIParserOutput{CLIParserType::ASSIGN}
    , _left{left}
    , _right{right}
  {}

  void AssignOutput::dump(std::ostream& s) const
  {
    s << "(";
    _left->dump(s);
    s << "=";
    _right->dump(s);
    s << ")";
  }

  CmdOutput::CmdOutput(const std::shared_ptr<TerminalOutput>& cmd,
                       const std::vector<std::shared_ptr<TerminalOutput>>& args,
                       const std::vector<std::shared_ptr<OptionOutput>>& opts)
    : CLIParserOutput{CLIParserType::COMMAND}
    , _cmd{cmd}
    , _args{args}
    , _opts{opts}
  {}

  void CmdOutput::dump(std::ostream& s) const
  {
    s << "\033[34m(\033[0m";
    _cmd->dump(s);
    s << "\033[32m(\033[0m";
    for (const auto& arg : _args)
      arg->dump(s);
    s << ",";
    for (const auto& opt : _opts)
      opt->dump(s);
    s << "\033[32m)\033[34m)\033[0m";
  }

  std::string CmdOutput::getCommand() const
  {
    return _cmd->getTerminal();
  }

  std::vector<std::shared_ptr<TerminalOutput>> CmdOutput::getArgs() const
  {
    return _args;
  }

  std::vector<std::shared_ptr<OptionOutput>> CmdOutput::getOpts() const
  {
    return _opts;
  }

  void CmdOutputBuilder::setCmd(const std::shared_ptr<TerminalOutput>& cmd)
  {
    _cmd = cmd;
  }

  void CmdOutputBuilder::addArg(const std::shared_ptr<TerminalOutput>& arg)
  {
    _args.emplace_back(arg);
  }

  void CmdOutputBuilder::addOpt(const std::shared_ptr<OptionOutput>& opt)
  {
    _opts.emplace_back(opt);
  }

  CmdOutputBuilder& CmdOutputBuilder::clear()
  {
    _cmd = createCLIParserOutput<TerminalOutput>("");
    _args.clear();
    _opts.clear();
    return *this;
  }

  std::shared_ptr<CmdOutput> CmdOutputBuilder::build()
  {
    return createCLIParserOutput<CmdOutput>(_cmd, _args, _opts);
  }

  EOLOutput::EOLOutput()
    : CLIParserOutput{CLIParserType::EOL}
  {}

  void EOLOutput::dump(std::ostream&) const
  {}

  CancelOutput::CancelOutput()
    : CLIParserOutput{CLIParserType::CANCEL}
  {}

  void CancelOutput::dump(std::ostream&) const
  {}
} /* !lel */
