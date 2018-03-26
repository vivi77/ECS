#include "CLIProducer.hh"
#include <iostream>
#include <algorithm>

namespace lel
{
  namespace details
  {
    inline char extractChar(std::string& s)
    {
      if (s.empty())
        return 0;

      char c = s.front();
      s.erase(std::begin(s));
      return c;
    }

    bool isBlank(const char c)
    {
      return ::isblank(c);
    }

    bool isStringChar(const char c)
    {
      static const char notStrChar[] = {'\0', '-', '=', '\n'};
      return !isBlank(c) &&
        std::find(std::begin(notStrChar), std::end(notStrChar), c) == std::end(notStrChar);
    }
  }

  CLIProducerOutput::CLIProducerOutput(const std::string& o, Type t)
    : _output{o}
    , _type{t}
  {}

  CLIProducerOutput CLIProducerOutput::getEndOutput()
  {
    return {"", Type::END};
  }

  std::string CLIProducerOutput::getOutput() const
  {
    return _output;
  }

  CLIProducerOutput::Type CLIProducerOutput::getType() const
  {
    return _type;
  }

  // CLIProducer
  CLIProducer::CLIProducer(const std::string& product)
    : _product{product}
  {}

  void CLIProducer::feed(const std::string& product)
  {
    _product += product;
  }

  CLIProducer::Output CLIProducer::parseExpression(const Precedence)
  {
    if (_product.empty())
    {
      std::cout << "Need more input ? ";
      std::string input;
      std::getline(std::cin, input);
      if (std::cin.good())
      {
        if (input.empty())
          input += "\n";
        input += "\n";
      }
      else if (std::cin.eof())
      {
        std::cin.clear();
        feed("\n");
        return {"", Type::CTRL_D};
      }
      std::cin.clear();
      feed(input);
    }

    auto c = details::extractChar(_product);
    while (details::isBlank(c))
      c = details::extractChar(_product);

    if (c == '-')
      return {std::string(1, c), Type::DASH};
    else if (c == '=')
      return {std::string(1, c), Type::EQUAL};
    else if (c == '\n')
      return {std::string(1, c), Type::EOL};
    else if (details::isStringChar(c))
    {
      std::string o(1, c);
      c = (_product.empty() ? 0 : _product[0]);
      while (details::isStringChar(c))
      {
        details::extractChar(_product);
        o += c;
        c = (_product.empty() ? 0 : _product[0]);
      }
      return {o, Type::STRING};
    }
    else if (c != 0)
      return {std::string(1, c), Type::UNKNOWN};
    return {"", Type::END};
  }

  void CLIProducer::reset()
  {
    _product.clear();
  }

  CLIProducer::Type CLIProducer::getOutputType(const Output& o)
  {
    return o.getType();
  }
} /* !lel */

std::ostream& operator<<(std::ostream& s, const lel::CLIProducerOutput& o)
{
  s << "{" << o.getOutput() << ", " << o.getType() << "}";
  return s;
}

std::ostream& operator<<(std::ostream& s, const lel::CLIProducerType& t)
{
  switch (t)
  {
  case lel::CLIProducerType::DASH: s << "DASH"; break;
  case lel::CLIProducerType::EQUAL: s << "EQUAL"; break;
  case lel::CLIProducerType::EOL: s << "EOL"; break;
  case lel::CLIProducerType::CTRL_D: s << "CTRL_D"; break;
  case lel::CLIProducerType::STRING: s << "STRING"; break;
  case lel::CLIProducerType::UNKNOWN: s << "UNKNOWN"; break;
  case lel::CLIProducerType::END: s << "END"; break;
  }
  return s;
}
