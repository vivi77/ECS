#pragma once

#include "S/CRTPS.hpp"
#include "CLIParser/CLIParser.hh"

namespace lel::ecs::system
{
  class CLI : public CRTPS<CLI>, public event::IEListener
  {
  public:
    CLI(CoreProxy& proxy);
    ~CLI() override = default;
    void exec() override;
    void registerEntity(const EntityPtr&) override;
    void deregisterEntity(const EntityPtr&) override;
    void setup() override;
    void atRemove() override;

    void update(const EPtr&) override;

  private:
    CLIParser _cliparser;
    bool _enabled = true;

  public:
    constexpr static std::string_view name{"CLIParser"};
  };
} /* !lel::ecs::system */
