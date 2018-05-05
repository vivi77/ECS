#pragma once

#include "E/CRTPE.hpp"
#include "E/TextInputUpdaterEvents/textinputupdaterevents_export.h"

namespace lel::ecs::event
{
  template <typename ID>
  class TEXTINPUTUPDATEREVENTS_EXPORT TextInputUpdaterEventsOut :
    public CRTPE<TextInputUpdaterEventsOut>
  {
  public:
    enum class Type : char
    {
      INPUT_SEND
    };

  private:
    TextInputUpdaterEventsOut(const ID senderID)
      : _senderID{senderID}
      , _type{INPUT_SEND}
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

  private:
    ID _senderID;
    Type _type;
  };
} /* !lel::ecs::event */
