#pragma once

#include "CRTPS.hpp"
#include "IEListener.hh"
#include "log/Log.hh"

class DebugSystem : public CRTPS<DebugSystem>, public IEListener
{
public:
  virtual ~DebugSystem() = default;
  void exec() override;
  void update(const EPtr&) override;
  void registerEntity(const EntityPtr&) override;

private:
  lel::Log _log;
};
