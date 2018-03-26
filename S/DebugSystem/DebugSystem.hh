#pragma once

#include "CRTPS.hpp"
#include "IEListener.hh"
#include "Log.hh"
#include <fstream>

class DebugSystem : public CRTPS<DebugSystem>, public IEListener
{
public:
  DebugSystem();
  virtual ~DebugSystem() = default;
  void exec() override;
  void update(const EPtr&) override;
  void registerEntity(const EntityPtr&) override;
  void setup() override;
  void atRemove() override;

private:
  std::ofstream _logFile;
  lel::Log _log;
};
