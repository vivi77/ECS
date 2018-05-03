#pragma once

#include "C/CRTPC.hpp"

namespace lel::ecs::component
{
  namespace details
  {
    class BaseTextInput : public CRTPC<BaseTextInput>
    {
    public:
      BaseTextInput(const std::string& content = "", const bool active = true);
      BaseTextInput(const entity::IDEntity& entityOwnerID,
                const std::string& content = "",
                const bool active = true);
      ~BaseTextInput() override = default;

      void setContent(const std::string& content);
      void activateSending();
      void deactivateSending();
      void addChar(const char c);
      void removeLastChar();
      void setTriggerCharacter(const char c);

      std::string getContent() const;
      bool isSendActive() const;
      char getTriggerCharacter() const;

      void sendInput() const;

    private:
      bool _active = true;
      std::string _content = "";
      char _triggerCharacter = -1;
    };
  }

  namespace meta
  {
    template <class TextInputID>
    class TextInput : public details::BaseTextInput
    {
    public:
      TextInput(const TextInputID& id, const std::string& content = "", const bool active = true)
        : details::BaseTextInput{content, active}
        , _id{id}
      {}

      TextInput(const entity::IDEntity& entityOwnerID, const TextInput& id,
                const std::string& content = "",
                const bool active = true)
        : details::BaseTextInput{entityOwnerID, content, active}
        , _id{id}
      {}

      ~TextInput() override = default;

      TextInputID getTextInputID() const
      {
        return _id;
      }

    private:
      TextInputID _id;
    };
  } /* !meta */

  class TextInputStr : public meta::TextInput<std::string>
  {
    using TextInputID = std::string;

  public:
    TextInputStr(const std::string& id, const std::string& content = "", const bool active = true);
    TextInputStr(const entity::IDEntity& entityOwnerID, const std::string& id,
                 const std::string& content = "", const bool active = true);
    ~TextInputStr() override = default;
  };
} /* !lel::ecs::component */
