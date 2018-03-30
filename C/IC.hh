#pragma once

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      class IC
      {
      public:
        using ID = unsigned;

      public:
        virtual ~IC() = default;
        virtual ID getID() const = 0;
      };
    } /* !component */
  } /* !ecs */
} /* !lel */
