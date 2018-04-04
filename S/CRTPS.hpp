#pragma once

#include "S/IS.hh"
#include "E/IEListener.hh"
#include <type_traits>
#include <iostream>

namespace lel::ecs::system
{
  template <class D>
  class CRTPS : public IS
  {
  public:
    virtual ~CRTPS() = default;

    ID getID() const final
    {
      return getSystemID();
    }

    bool isListener() const final
    {
      return std::is_base_of_v<event::IEListener, D>;
    }

    static ID getSystemID()
    {
      return _id;
    }

  private:
    static ID _id;
  };

  namespace old
  {
    template <class D>
    class CRTPS : public IS
    {
      using ID = typename IS::ID;

    public:
      virtual ~CRTPS() = default;

      static void assignID(const ID id)
      {
        if (!isIDAssigned())
        {
          _id = id;
          _idAssigned = true;
        }
      }

      ID getID() const final
      {
        return getSystemID();
      }

      bool isListener() const final
      {
        return std::is_base_of_v<event::IEListener, D>;
      }

      static ID getSystemID()
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
    typename CRTPS<D>::ID CRTPS<D>::_id = 0;

    template <class D>
    bool CRTPS<D>::_idAssigned = false;
  } /* !old */
} /* !lel::ecs::system */
