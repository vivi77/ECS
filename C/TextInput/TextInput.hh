#pragma once

#include "C/CRTPC.hpp"

namespace lel::ecs::component
{
  namespace details
  {
    class BaseTextInput
    {
    public:
      BaseTextInput(const std::string& input = "", const bool active = true);

      void setInput(const std::string& input);
      void activateSending();
      void deactivateSending();
      void addChar(const char c);
      void removeLastChar();
      void setTriggerCharacter(const char c);

      std::string getInput() const;
      bool isSendActive() const;
      char getTriggerCharacter() const;

    private:
      bool _active = true;
      std::string _input = "";
      char _triggerCharacter = -1;
    };
  }

  namespace meta
  {
    template <class TextInputID>
    class TextInput : public details::BaseTextInput, public CRTPC<TextInput<TextInputID>>
    {
    public:
      TextInput(const TextInputID& id, const std::string& input = "", const bool active = true)
        : details::BaseTextInput{input, active}
        , CRTPC<TextInput<TextInputID>>{}
        , _id{id}
      {}

      TextInput(const entity::IDEntity& entityOwnerID,
                const TextInputID& id,
                const std::string& input = "",
                const bool active = true)
        : details::BaseTextInput{input, active}
        , CRTPC<TextInput<TextInputID>>{entityOwnerID}
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
    TextInputStr(const std::string& id, const std::string& input = "", const bool active = true);
    TextInputStr(const entity::IDEntity& entityOwnerID, const std::string& id,
                 const std::string& input = "", const bool active = true);
    ~TextInputStr() override = default;
  };
} /* !lel::ecs::component */
