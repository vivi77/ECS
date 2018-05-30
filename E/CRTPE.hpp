#pragma once

#include "IE.hh"
#include "Utility/TemplateUniqueID.hpp"
#include "Utility/meta.hpp"
#include "E/IDEvent.hh"

namespace lel::ecs::event
{
  template <class D>
  class CRTPE : public IE, public meta::TemplateUniqueID<CRTPE<D>, IE::ID>
  {
  public:
    using ID = typename IE::ID;

  public:
    ~CRTPE() override = default;

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
      // Double 'check' MAYBE because of a bug in g++ 8.1 in which it does not
      // recognize the expression 'has_variable_name_v<D>' as a value-dependent
      // expression when the lambda has 1 parameter. But it do recognize it as
      // one when it is double
      if constexpr (meta::has_variable_name_v<D>
                    && meta::has_variable_name_v<D>)
        msg += D::name;
      else
        msg += typeid(D).name();
      msg += " EVENT has been attributed the ID#" + std::to_string(id);
    });
} /* !lel::ecs::event */
