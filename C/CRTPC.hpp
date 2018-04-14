#pragma once

#include "C/IC.hh"
#include "E/EManager/EManager.hh"
#include "Utility/TemplateUniqueID.hpp"
#include "Utility/meta.hpp"

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
      msg += " COMPONENT has been attributed the ID#" + std::to_string(id);
    });
} /* !lel::ecs::component */
