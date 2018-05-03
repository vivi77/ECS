#include "TextInput.hh"
#include "E/EManager/EManager.hh"

namespace lel::ecs::component
{
  namespace details
  {
    BaseTextInput::BaseTextInput(const std::string& content, const bool active)
      : CRTPC{}
      , _content{content}
      , _active{active}
    {}

    BaseTextInput::BaseTextInput(const entity::IDEntity& entityOwnerID,
                         const std::string& content,
                         const bool active)
      : CRTPC{entityOwnerID}
      , _content{content}
      , _active{active}
    {}

    void BaseTextInput::setContent(const std::string& content)
    {
      _content = content;
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
      _content += c;
    }

    void BaseTextInput::removeLastChar()
    {
      _content.pop_back();
    }

    void BaseTextInput::setTriggerCharacter(const char c)
    {
      _triggerCharacter = c;
    }

    std::string BaseTextInput::getContent() const
    {
      return _content;
    }

    bool BaseTextInput::isSendActive() const
    {
      return _active;
    }

    char BaseTextInput::getTriggerCharacter() const
    {
      return _triggerCharacter;
    }

    void BaseTextInput::sendInput() const
    {
      if (!_active)
        return ;
    }
  }

  TextInputStr::TextInputStr(const std::string& id,
                             const std::string& content,
                             const bool active)
    : meta::TextInput<TextInputStr::TextInputID>{id, content, active}
  {
  }

  TextInputStr::TextInputStr(const entity::IDEntity& entityOwnerID,
                             const std::string& id,
                             const std::string& content,
                             const bool active)
    : meta::TextInput<TextInputStr::TextInputID>{entityOwnerID, id, content, active}
  {
  }
} /* !lel::ecs::component */
