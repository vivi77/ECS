#pragma once

#include "S/IS.hh"
#include "S/CoreProxy/CoreProxy.hh"
#include "E/IEListener.hh"
#include "E/EManager/EManager.hh"
#include "E/DebugEvent/DebugEvent.hh"
#include "Utility/TemplateUniqueID.hpp"
#include "Utility/meta.hpp"

namespace lel::ecs::system
{
  template <class D>
  class CRTPS : public IS, public meta::TemplateUniqueID<CRTPS<D>, IS::ID>
  {
    using ID = typename IS::ID;

  public:
    CRTPS(std::unique_ptr<CoreProxy>& proxy)
      : _proxy{std::move(proxy)}
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

    std::unique_ptr<CoreProxy>& getProxy()
    {
      return _proxy;
    }

    static ID getSystemID()
    {
      return _id;
    }

  private:
    static ID _id;
    std::unique_ptr<CoreProxy> _proxy;
  };

  template <class D>
  typename CRTPS<D>::ID CRTPS<D>::_id = CRTPS<D>::generateID(
    [](auto id)
    {
      std::string msg;
      if constexpr (meta::has_variable_name_v<D>)
        msg += D::name;
      else
        msg += typeid(D).name();
      msg += " SYSTEM has been attributed the ID#" + std::to_string(id);
      //event::EManager::fire<event::DebugEvent>(msg);
    });
} /* !lel::ecs::system */
