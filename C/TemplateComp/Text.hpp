#pragma once

#include "DefaultInfo.hh"
#include "C/CRTPC.hpp"

namespace lel::ecs::component::templateComponent
{
  template <class Color, class Info = details::DefaultInfo>
  struct Text : public CRTPC<Text<Color, Info>>, public Color, public Info
  {
  public:
    using ColorClass = Color;

  public:
    template <typename ... Args>
    Text(const char* txt = "", Args&& ... args)
      : CRTPC<Text<Color, Info>>{}
      , Color{std::forward<Args>(args)...}
      , text{txt}
    {}

    ~Text() override = default;

  public:
    const char* text = "";
  };
} /* !lel::ecs::component::templateComponent */
