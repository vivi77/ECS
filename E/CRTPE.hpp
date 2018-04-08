#pragma once

#include "IE.hh"
#include "Utility/TemplateUniqueID.hpp"
#include "E/EManager.hh"
#include "E/DebugEvent/DebugEvent.hh"
#include "Utility/meta.hpp"
#include <iostream>

namespace lel::ecs::event
{
  template <class D>
  class CRTPE : public IE, public meta::TemplateUniqueID<CRTPE<D>, IE::ID>
  {
  public:
    using ID = typename IE::ID;

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

  private:
    static ID _id;
  };

  template <class D>
  typename CRTPE<D>::ID CRTPE<D>::_id = CRTPE<D>::generateID(
    [](auto id)
    {
      std::string msg;
      if constexpr (meta::has_variable_name_v<D>)
        msg += D::name;
      else
        msg += typeid(D).name();
      msg += " EVENT has been attributed the ID#" + std::to_string(id);
      event::EManager::fire<event::DebugEvent>(msg);
    });

  namespace old
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
  } /* !old */
} /* !lel::ecs::event */
