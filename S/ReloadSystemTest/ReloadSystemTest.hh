#pragma once

#include "S/CRTPS.hpp"

namespace lel::ecs::system
{
  class ReloadSystemTest : public CRTPS<ReloadSystemTest>
  {
  public:
    ReloadSystemTest(CoreProxy& proxy);
    ~ReloadSystemTest() override = default;

    void exec() override;
    void registerEntity(const EntityPtr&) override;
    void deregisterEntity(const EntityPtr&) override;
    void setup() override;
    void atRemove() override;

  private:
  };
} /* !lel::ecs::system */
