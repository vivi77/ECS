#pragma once

#include "IE.hh"

namespace lel
{
  namespace ecs
  {
    namespace event
    {
      template <class D>
      class CRTPE : public IE
      {
      public:
        using ID = IE::ID;

      public:
        virtual ~CRTPE() = default;

        ID getID() const final
        {
          return getEventID();
        }

        static ID getEventID()
        {
          return _id;
        }

        static void assignID(const ID id)
        {
          if (!isIDAssigned())
          {
            _id = id;
            _idAssigned = true;
          }
        }

        static bool isIDAssigned()
        {
          return _idAssigned;
        }

      private:
        static ID _id;
        static bool _idAssigned;
      };

      template <class D>
      typename CRTPE<D>::ID CRTPE<D>::_id = 0;

      template <class D>
      bool CRTPE<D>::_idAssigned = false;
    } /* !event */
  } /* !ecs */
} /* !lel */
