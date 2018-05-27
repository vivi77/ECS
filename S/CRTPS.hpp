#pragma once

#include "S/IS.hh"
#include "S/CoreProxy/CoreProxy.hh"
#include "S/IDSystem.hh"
#include "E/IEListener.hh"
#include "E/EManager/EManager.hh"
#include "Utility/TemplateUniqueID.hpp"
#include "Utility/meta.hpp"

namespace lel::ecs::system
{
  template <class D>
  class CRTPS : public IS, public meta::TemplateUniqueID<CRTPS<D>, IS::ID>
  {
    using ID = typename IS::ID;

  public:
    CRTPS(CoreProxy& proxy)
      : _proxy{proxy}
    {}

    virtual ~CRTPS() = default;

    ID getID() const final
    {
      return getSystemID();
    }

    bool isListener() const final
    {
      return std::is_base_of_v<event::IEListener, D>;
    }

    CoreProxy& getProxy()
    {
      return _proxy;
    }

    static ID getSystemID()
    {
      return _id;
    }

  private:
    static ID _id;
    CoreProxy& _proxy;
  };

  template <class D>
  typename CRTPS<D>::ID CRTPS<D>::_id = CRTPS<D>::generateID(
    [](auto id)
    {
      std::string msg;
      // Double 'check' MAYBE because of a bug in g++ 8.1 in which it does not
      // recognize the expression 'has_variable_name_v<D>' as a value-dependent
      // expression when the lambda has 1 parameter. But it do recognize it as
      // one when it is double
      if constexpr (meta::has_variable_name_v<D>
                    && meta::has_variable_name_v<D>)
        msg += D::name;
      else
        msg += typeid(D).name();
      msg += " SYSTEM has been attributed the ID#" + std::to_string(id);
    });
} /* !lel::ecs::system */
