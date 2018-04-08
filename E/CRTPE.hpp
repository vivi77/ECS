#pragma once

#include "IE.hh"
#include "E/EManager/EManager.hh"
#include "E/DebugEvent/DebugEvent.hh"
#include "Utility/TemplateUniqueID.hpp"
#include "Utility/meta.hpp"

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
      EManager::fire<event::DebugEvent>(msg);
    });
} /* !lel::ecs::event */
