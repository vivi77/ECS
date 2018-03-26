#pragma once

#include "Parser_concept.hpp"
#include <optional>
#include <string>
#include <deque>

namespace lel
{
  enum class CLIProducerType { STRING, DASH, EQUAL, EOL, CTRL_D, UNKNOWN, END, };
  enum class CLIProducerPrecedence { DEFAULT, };

  class CLIProducerOutput
  {
    using Type = CLIProducerType;

  public:
    CLIProducerOutput(const std::string& o, Type t);
    static CLIProducerOutput getEndOutput();

    std::string getOutput() const;
    Type getType() const;

  private:
    std::string _output;
    Type _type;
  };

  class CLIProducer
  {
  public:
    //Required by concept::parser::InputProducer
    using Type = CLIProducerType;
    using Output = CLIProducerOutput;
    using Precedence = CLIProducerPrecedence;

  public:
    CLIProducer(const std::string& product = "");
    void feed(const std::string& product);

    //Required by concept::parser::InputProducer
    Output parseExpression([[maybe_unused]] const Precedence = Precedence::DEFAULT);
    void reset();
    static Type getOutputType(const Output& o);

  private:
    std::string _product;

    static_assert(concept::InputProducer<CLIProducer>::value);
  };
} /* !lel */

std::ostream& operator<<(std::ostream&, const lel::CLIProducerOutput&);
std::ostream& operator<<(std::ostream&, const lel::CLIProducerType&);
