#pragma once

#include "E/CRTPE.hpp"

namespace lel::ecs::event
{
  class CoreCommandsEvent : public CRTPE<CoreCommandsEvent>
  {
  public:
    enum class Type
    {
      CTRL_D,
      INPUT
    };

  public:
    CoreCommandsEvent();
    CoreCommandsEvent(const std::string& input);
    ~CoreCommandsEvent() override = default;

    Type getType() const;
    std::string getInput() const;

  private:
    Type _type;
    std::string _input = "";
  };
} /* !lel::ecs::event */
