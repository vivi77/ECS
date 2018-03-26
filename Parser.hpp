#pragma once

#include "Parser_concept.hpp"
#include <deque>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>

namespace lel
{
  template <typename C, typename K, typename V>
  void registerInMap(C& container, const K& key, const V& value)
  {
     auto it = container.find(key);
     if (it == std::end(container))
       container.insert(std::make_pair(key, value));
  }

  template <class InputProducer, class ParserPolicy>
  class Parser
  {
  public:
    using PP = ParserPolicy;
    using Precedence = typename PP::Precedence;
    using Output = typename PP::Output;

  public:
    using IP = InputProducer;
    using Input = typename IP::Output;
    using Type = typename IP::Type;

  public:
    class IPrefixParselet
    {
    public:
      virtual ~IPrefixParselet() = default;
      virtual Output parse(Parser& parser, const Input& input) = 0;
    };

    class IInfixParselet
    {
    public:
      virtual ~IInfixParselet() = default;
      virtual Output parse(Parser& parser, const Output& leftExpr, const Input& input) = 0;
      virtual Precedence getPrecedence() const = 0;
    };

  using PrefixParseletPtr = std::shared_ptr<IPrefixParselet>;
  using InfixParseletPtr = std::shared_ptr<IInfixParselet>;

  public:
    Parser(IP& p)
      : _p{p}
    {}

    Output parseExpression(const Precedence precedence = PP::getDefaultPrecedence())
    {
      auto input = this->consume();
      auto prefix = _prefixParselets.find(IP::getOutputType(input));
      if (prefix == std::end(_prefixParselets))
        throw std::runtime_error{"PrefixParselet not found"};

      auto left = prefix->second->parse(*this, input);

      while (1)
      {
        auto nextInput = this->lookAhead(0);
        auto infix = _infixParselets.find(IP::getOutputType(nextInput));
        Precedence currentPrec = (infix == std::end(_infixParselets) ?
                                  PP::getDefaultPrecedence() :
                                  infix->second->getPrecedence());
        if (precedence < currentPrec)
        {
          this->consume();
          left = infix->second->parse(*this, left, nextInput);
        }
        else
          break;
      }
      return left;
    }

    Input consume(const std::vector<Type>& types)
    {
      auto input = lookAhead(0);
      auto beginIt = std::begin(types);
      auto endIt = std::end(types);
      auto it = std::find(beginIt, endIt, IP::getOutputType(input));
      if (it == endIt)
        throw std::runtime_error{"Parser::consume: Requested type not correct"};
      _lookAheadBuffer.pop_front();
      return input;
    }

    Input consume(const Type type)
    {
      auto input = lookAhead(0);
      if (IP::getOutputType(input) != type)
        throw std::runtime_error{"Parser::consume: Requested type not correct"};
      _lookAheadBuffer.pop_front(); // == .erase(std::begin(_lookAheadBuffer))
      return input;
    }

    Input consume()
    {
      auto input = lookAhead(0);
      _lookAheadBuffer.pop_front(); // == .erase(std::begin(_lookAheadBuffer))
      return input;
    }

    Input lookAhead(const unsigned dist)
    {
      while (_lookAheadBuffer.size() <= dist)
        _lookAheadBuffer.emplace_back(_p.parseExpression());
      return _lookAheadBuffer[dist];
    }

    void registerPrefix(const Type key, const PrefixParseletPtr& parselet)
    {
      registerInMap(_prefixParselets, key, parselet);
    }

    void registerInfix(const Type key, const InfixParseletPtr& parselet)
    {
      registerInMap(_infixParselets, key, parselet);
    }

    void reset()
    {
      _p.reset();
      _lookAheadBuffer.clear();
    }

  private:
    IP& _p;
    std::unordered_map<Type, PrefixParseletPtr> _prefixParselets;
    std::unordered_map<Type, InfixParseletPtr> _infixParselets;
    std::deque<Input> _lookAheadBuffer;

    static_assert(concept::InputProducer<InputProducer>::value);
    static_assert(concept::ParserPolicy<ParserPolicy>::value);
  };
} /* !lel */
