#pragma once

#include "CRTPS.hpp"
#include "parsing/CLIParser.hh"

class CLISystem : public CRTPS<CLISystem>
{
public:
  CLISystem();
  virtual ~CLISystem() = default;
  void exec() override;

private:
  lel::CLIProducer cliproducer;
  lel::CLIParser cliparser;
};
