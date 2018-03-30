#pragma once

#include "S/CRTPS.hpp"
#include "S/NCurses/ncursessystem_export.h"
#include "C/TerminalText/TerminalText.hh"
#include "C/Transform/Transform.hh"
#include <vector>

namespace lel
{
  namespace ecs
  {
    namespace system
    {
      class NCURSESSYSTEM_EXPORT NCurses : public CRTPS<NCurses>
      {
      public:
        using DrawablePtr = std::shared_ptr<component::TerminalText>;
        using TransformPtr = std::shared_ptr<component::Transform>;

      private:
        struct NCursesData
        {
          TransformPtr transform;
          DrawablePtr drawableComp;

          bool isValid() const
          {
            return drawableComp != nullptr && transform != nullptr;
          }
        };

      public:
        virtual ~NCurses() = default;

        void exec() override;
        void registerEntity(const EntityPtr&) override;
        void setup() override;
        void atRemove() override;

      private:
        std::vector<NCursesData> _data;
      };
    } /* !system */
  } /* !ecs */
} /* !lel */
