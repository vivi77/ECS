#pragma once

#include "S/CRTPS.hpp"
#include "Log.hh"
#include <fstream>

namespace lel::ecs::system
{
  class Debug : public CRTPS<Debug>, public event::IEListener
  {
  public:
    Debug(CoreProxy&);
    ~Debug() override = default;
    void exec() override;
    void update(const EPtr&) override;
    void registerEntity(const EntityPtr&) override;
    void deregisterEntity(const EntityPtr&) override;
    void setup() override;
    void atRemove() override;

  private:
    std::ofstream _logFile;
    lel::Log _log;

  private:
    static constexpr std::string_view name{"Debug"};
  };
} /* !lel::ecs::system */
