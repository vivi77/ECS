#pragma once

#include "E/CRTPE.hpp"
#include "E/TextInputUpdaterEvents/textinputupdaterevents_export.h"

namespace lel::ecs::event
{
  template <typename ID>
  class TEXTINPUTUPDATEREVENTS_EXPORT TextInputUpdaterEventsIn :
    public CRTPE<TextInputUpdaterEventsIn>
  {
  public:
    enum class Type : char
    {
      ADD_CHAR,
      REMOVE_CHAR
    };

  public:
    TextInputUpdaterEventsIn(const ID senderID)
      : _senderID{senderID}
      , _type{REMOVE_CHAR}
    {}

    TextInputUpdaterEventsIn(const ID senderID, const char c)
      : _senderID{senderID}
      , _type{ADD_CHAR}
      , _character{c}
    {}

    ~TextInputUpdaterEventsIn() override = default;

    ID getSenderID() const
    {
      return _senderID;
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
    ID _senderID;
    Type _type;
    char _character = 0;
  };
} /* !lel::ecs::event */
