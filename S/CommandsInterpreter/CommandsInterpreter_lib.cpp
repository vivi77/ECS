#include "CommandsInterpreter.hh"
#include "S/CommandsInterpreter/commandsinterpreter_export.h"

extern "C"
{
  COMMANDSINTERPRETER_EXPORT lel::ecs::system::IS* create(lel::ecs::CoreProxy* proxy)
  {
    std::unique_ptr<lel::ecs::CoreProxy> proxyPtr{proxy};
    return new lel::ecs::system::CommandsInterpreter(proxyPtr);
  }

  COMMANDSINTERPRETER_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}
