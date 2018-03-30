#pragma once

namespace lel
{
  namespace ecs
  {
    namespace event
    {
      class IE
      {
      public:
        using ID = unsigned;

      public:
        virtual ~IE() = default;
        virtual ID getID() const = 0;
      };
    } /* !event */
  } /* !ecs */
} /* !lel */
