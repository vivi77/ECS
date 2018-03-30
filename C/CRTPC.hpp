#pragma once

#include "C/IC.hh"

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      template <class D>
      class CRTPC : public IC
      {
      public:
        using ID = IC::ID;

      public:
        virtual ~CRTPC() = default;

        ID getID() const final
        {
          return getComponentID();
        }

        static void assignID(const ID id)
        {
          if (!isIDAssigned())
          {
            _id = id;
            _idAssigned = true;
          }
        }

        static ID getComponentID()
        {
          return _id;
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
      typename CRTPC<D>::ID CRTPC<D>::_id = 0;

      template <class D>
      bool CRTPC<D>::_idAssigned = false;
    } /* !component */
  } /* !ecs */
} /* !lel */
