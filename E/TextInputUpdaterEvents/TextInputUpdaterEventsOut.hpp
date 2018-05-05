#pragma once

#include "E/CRTPE.hpp"

namespace lel::ecs::event
{
  template <typename ID>
  class TextInputUpdaterEventsOut : public CRTPE<TextInputUpdaterEventsOut<ID>>
  {
  public:
    enum class Type : char
    {
      INPUT_SEND
    };

  public:
    TextInputUpdaterEventsOut(const ID senderID, const std::string& input)
      : _senderID{senderID}
      , _type{Type::INPUT_SEND}
      , _input{input}
    {}

    ~TextInputUpdaterEventsOut() override = default;

    ID getSenderID() const
    {
      return _senderID;
    }

    Type getType() const
    {
      return _type;
    }

    std::string getInput() const
    {
      return _input;
    }

  private:
    ID _senderID;
    Type _type;
    std::string _input;
  };
} /* !lel::ecs::event */
