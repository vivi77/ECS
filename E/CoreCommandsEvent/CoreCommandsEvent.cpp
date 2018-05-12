#include "CoreCommandsEvent.hh"

namespace lel::ecs::event
{
  CoreCommandsEvent::CoreCommandsEvent(const std::string& input)
    : CRTPE{}
    , _input{input}
  {}

  std::string CoreCommandsEvent::getInput() const
  {
    return _input;
  }
} /* !lel::ecs::event */
