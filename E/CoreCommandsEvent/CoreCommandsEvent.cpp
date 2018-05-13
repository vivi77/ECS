#include "CoreCommandsEvent.hh"

namespace lel::ecs::event
{
  CoreCommandsEvent::CoreCommandsEvent()
    : CRTPE{}
    , _type{Type::CTRL_D}
  {}

  CoreCommandsEvent::CoreCommandsEvent(const std::string& input)
    : CRTPE{}
    , _type{Type::INPUT}
    , _input{input}
  {}

  CoreCommandsEvent::Type CoreCommandsEvent::getType() const
  {
    return _type;
  }

  std::string CoreCommandsEvent::getInput() const
  {
    return _input;
  }
} /* !lel::ecs::event */
