#pragma once

#include "C/CRTPC.hpp"
#include <functional>

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      template <class Color>
      struct TemplateText : public CRTPC<TemplateText<Color>>, public Color
      {
      public:
        using ColorClass = Color;

      public:
        template <typename ... Args>
        TemplateText(const char* txt, Args&& ... args)
          : CRTPC<TemplateText<Color>>{}
          , Color{std::forward<Args>(args)...}
          , text{txt}
        {}

        virtual ~TemplateText() = default;

      public:
        const char* text;
      };
    } /* !component */
  } /* !ecs */
} /* !lel */
