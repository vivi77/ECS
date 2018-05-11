#include "CommandsInterpreter.hh"
#include "S/CommandsInterpreter/commandsinterpreter_export.h"

extern "C"
{
  COMMANDSINTERPRETER_EXPORT lel::ecs::system::IS* create(lel::ecs::CoreProxy& proxy)
  {
    return new lel::ecs::system::CommandsInterpreter(proxy);
  }

  COMMANDSINTERPRETER_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}
