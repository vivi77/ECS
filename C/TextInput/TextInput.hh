#pragma once

#include "C/CRTPC.hpp"

namespace lel::ecs::component
{
  namespace details
  {
    struct BaseTextInput
    {
      BaseTextInput(const std::string& input = "", const bool active = true);

      bool active = true;
      std::string input = "";
      char triggerCharacter = -1;
    };
  } /* !details */

  namespace meta
  {
    template <class TextInputID>
    struct TextInput : public details::BaseTextInput, public CRTPC<TextInput<TextInputID>>
    {
      TextInput(const TextInputID& inputId, const std::string& input = "", const bool active = true)
        : details::BaseTextInput{input, active}
        , CRTPC<TextInput<TextInputID>>{}
        , textInputID{inputId}
      {}

      TextInput(const entity::IDEntity& entityOwnerID,
                const TextInputID& inputId,
                const std::string& input = "",
                const bool active = true)
        : details::BaseTextInput{input, active}
        , CRTPC<TextInput<TextInputID>>{entityOwnerID}
        , textInputID{inputId}
      {}

      ~TextInput() override = default;

      TextInputID textInputID;
    };
  } /* !meta */

  inline void removeLastChar(details::BaseTextInput& input)
  {
    if (input.active && !input.input.empty())
      input.input.pop_back();
  }

  using TextInputStr = meta::TextInput<std::string>;
} /* !lel::ecs::component */
