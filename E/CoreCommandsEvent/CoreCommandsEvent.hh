#pragma once

#include "E/CRTPE.hpp"

namespace lel::ecs::event
{
  class CoreCommandsEvent : public CRTPE<CoreCommandsEvent>
  {
  public:
    CoreCommandsEvent(const std::string& input);
    ~CoreCommandsEvent() override = default;

    std::string getInput() const;

  private:
    std::string _input;
  };
} /* !lel::ecs::event */
