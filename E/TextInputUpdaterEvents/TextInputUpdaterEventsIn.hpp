#pragma once

#include "E/CRTPE.hpp"

namespace lel::ecs::event
{
  template <typename ID>
  class TextInputUpdaterEventsIn : public CRTPE<TextInputUpdaterEventsIn<ID>>
  {
  public:
    enum class Type : char
    {
      ADD_CHAR,
      REMOVE_CHAR
    };

  public:
    TextInputUpdaterEventsIn(const ID receiverID)
      : _receiverID{receiverID}
      , _type{Type::REMOVE_CHAR}
    {}

    TextInputUpdaterEventsIn(const ID receiverID, const char c)
      : _receiverID{receiverID}
      , _type{Type::ADD_CHAR}
      , _character{c}
    {}

    ~TextInputUpdaterEventsIn() override = default;

    ID getReceiverID() const
    {
      return _receiverID;
    }

    Type getType() const
    {
      return _type;
    }

    char getChar() const
    {
      return _character;
    }

  private:
    ID _receiverID;
    Type _type;
    char _character = 0;
  };
} /* !lel::ecs::event */
