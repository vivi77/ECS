#pragma once

#include "C/CRTPC.hpp"
#include <functional>

namespace lel::ecs::component::templateComponent
{
  template <class Color>
  struct Text : public CRTPC<Text<Color>>, public Color
  {
  public:
    using ColorClass = Color;

  public:
    template <typename ... Args>
    Text(const char* txt, Args&& ... args)
      : CRTPC<Text<Color>>{}
      , Color{std::forward<Args>(args)...}
      , text{txt}
    {}

    virtual ~Text() = default;

  public:
    const char* text;
  };
} /* !lel::ecs::component::templateComponent */
