#include "TextInput.hh"
#include "E/EManager/EManager.hh"

#include <iostream>

namespace lel::ecs::component
{
  namespace details
  {
    BaseTextInput::BaseTextInput(const std::string& input, const bool active)
      : _active{active}
      , _input{input}
    {
    }

    void BaseTextInput::setInput(const std::string& input)
    {
      _input = input;
    }

    void BaseTextInput::activateSending()
    {
      _active = true;
    }

    void BaseTextInput::deactivateSending()
    {
      _active = false;
    }

    void BaseTextInput::addChar(const char c)
    {
      _input += c;
    }

    void BaseTextInput::removeLastChar()
    {
      _input.pop_back();
    }

    void BaseTextInput::setTriggerCharacter(const char c)
    {
      _triggerCharacter = c;
    }

    std::string BaseTextInput::getInput() const
    {
      return _input;
    }

    bool BaseTextInput::isSendActive() const
    {
      return _active;
    }

    char BaseTextInput::getTriggerCharacter() const
    {
      return _triggerCharacter;
    }
  }

  TextInputStr::TextInputStr(const std::string& id,
                             const std::string& input,
                             const bool active)
    : meta::TextInput<TextInputStr::TextInputID>{id, input, active}
  {
  }

  TextInputStr::TextInputStr(const entity::IDEntity& entityOwnerID,
                             const std::string& id,
                             const std::string& input,
                             const bool active)
    : meta::TextInput<TextInputStr::TextInputID>{entityOwnerID, id, input, active}
  {
  }
} /* !lel::ecs::component */
