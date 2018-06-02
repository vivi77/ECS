#include "CLIParser.hh"
#include "CLIParserParselets.hh"
#include <vector>

namespace lel
{
  CLIParserOutput::CLIParserOutput(const CLIParserOutput::Type type)
    : _type{type}
  {}

  CLIParserOutput::Type CLIParserOutput::getType() const
  {
    return _type;
  }

  CLIParserOutPolicy::Precedence CLIParserOutPolicy::getDefaultPrecedence()
  {
    return Precedence::EXPR;
  }

  CLIParser::CLIParser()
    : Parser{_p}
    , _p{}
  {
    registerPrefix(CLIProducerType::STRING, std::make_shared<CommandParselet>());
    registerPrefix(CLIProducerType::DASH, std::make_shared<OptionParselet>());
    registerPrefix(CLIProducerType::EOL, std::make_shared<EOLParselet>());
    registerPrefix(CLIProducerType::CTRL_D, std::make_shared<CancelParselet>());

    registerInfix(CLIProducerType::EQUAL, std::make_shared<InfixAssignParselet>());
    registerInfix(CLIProducerType::STRING, std::make_shared<InfixCmdArgParselet>());
    registerInfix(CLIProducerType::DASH, std::make_shared<InfixCmdArgParselet>());
  }

  CLIParser::IP& CLIParser::getProducer()
  {
    return _p;
  }
} /* !lel */

std::ostream& operator<<(std::ostream& s, const lel::CLIParserType& t)
{
  switch (t)
  {
    case lel::CLIParserType::ASSIGN: s << "ASSIGN"; break;
    case lel::CLIParserType::CANCEL: s << "CANCEL"; break;
    case lel::CLIParserType::COMMAND: s << "COMMAND"; break;
    case lel::CLIParserType::EOL: s << "EOL"; break;
    case lel::CLIParserType::OPTION: s << "OPTION"; break;
    case lel::CLIParserType::TERMINAL: s << "TERMINAL"; break;
  }
  return s;
}
