#pragma once

#include "S/CRTPS.hpp"
#include "E/IEListener.hh"

namespace lel::ecs::system
{
  class CoreCommands : public CRTPS<CoreCommands>, public event::IEListener
  {
  public:
    CoreCommands(CoreProxy& proxy);
    ~CoreCommands() override = default;

    void exec() override;
    void registerEntity(const EntityPtr&) override;
    void deregisterEntity(const EntityPtr&) override;
    void setup() override;
    void atRemove() override;

    void update(const EPtr&) override;

  private:

  };
} /* !lel::ecs::system */
