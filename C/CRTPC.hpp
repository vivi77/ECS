#pragma once

#include "C/BaseComp/BaseComp.hh"
#include "C/IDComponent.hh"
#include "Utility/TemplateUniqueID.hpp"
#include "Utility/meta.hpp"

namespace lel::ecs::component
{
  template <class D>
  class CRTPC : public BaseComp, public meta::TemplateUniqueID<CRTPC<D>, IC::ID>
  {
    using ID = typename IC::ID;

  public:
    CRTPC() = default;

    CRTPC(const entity::IDEntity& entityOwnerID)
      : BaseComp{entityOwnerID}
    {}

    ~CRTPC() override = default;

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
      // Double 'check' MAYBE because of a bug in g++ 8.1 in which it does not
      // recognize the expression 'has_variable_name_v<D>' as a value-dependent
      // expression when the lambda has 1 parameter. But it do recognize it as
      // one when it is double
      if constexpr (meta::has_variable_name_v<D> &&
                    meta::has_variable_name_v<D>)
        msg += D::name;
      else
        msg += typeid(D).name();
      msg += " COMPONENT has been attributed the ID#" + std::to_string(id);
    });
} /* !lel::ecs::component */
