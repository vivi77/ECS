#pragma once

#include "C/IC.hh"
#include "Utility/TemplateUniqueID.hpp"
#include "E/EManager.hh"
#include "E/DebugEvent/DebugEvent.hh"
#include "lel_library/meta/type_traits_has.hpp"

namespace lel::ecs::meta
{
  METACONCEPT_HAS_VARIABLE(name);
} /* !lel::ecs::meta */

namespace lel::ecs::component
{
  template <class D>
  class CRTPC : public IC, public meta::TemplateUniqueID<CRTPC<D>, IC::ID>
  {
    using ID = typename IC::ID;

  public:
    virtual ~CRTPC() = default;
    ID getID() const final
    {
      return getComponentID();
    }

    static ID getComponentID()
    {
      return _id;
    }

  private:
    static ID _id;
  };

  template <class D>
  typename CRTPC<D>::ID CRTPC<D>::_id = CRTPC<D>::generateID(
    [](auto id)
    {
      std::string msg;
      if constexpr (meta::has_variable_name_v<D>)
        msg += D::name;
      else
        msg += typeid(D).name();
      msg += " has been attributed the ID#" + std::to_string(id);
      event::EManager::fire<event::DebugEvent>(msg);
    });

  namespace old
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
  } /* !old */
} /* !lel::ecs::component */
