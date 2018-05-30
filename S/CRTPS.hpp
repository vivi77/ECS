#pragma once

#include "S/IS.hh"
#include "S/CoreProxy/CoreProxy.hh"
#include "S/IDSystem.hh"
#include "E/IEListener.hh"
#include "Utility/meta.hpp"

//For convenience
#include "S/Utility/macros.hh"

namespace lel::ecs::system
{
  extern IDSystem g_systemID;

  template <class D>
  class CRTPS : public IS
  {
    using ID = typename IS::ID;

  public:
    CRTPS(CoreProxy& proxy)
      : _proxy{proxy}
    {}

    ~CRTPS() override = default;

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
      return g_systemID;
    }

  private:
    CoreProxy& _proxy;
  };
} /* !lel::ecs::system */
