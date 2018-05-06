#include "TextInput.hh"
#include "E/EManager/EManager.hh"

namespace lel::ecs::component
{
  namespace details
  {
    BaseTextInput::BaseTextInput(const std::string& input, const bool active)
      : active{active}
      , input{input}
    {
    }
  }
} /* !lel::ecs::component */
