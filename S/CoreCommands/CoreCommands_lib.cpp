#include "CoreCommands.hh"
#include "S/CoreCommands/corecommands_export.h"

extern "C"
{
  CORECOMMANDS_EXPORT lel::ecs::system::IS* create(lel::ecs::CoreProxy& proxy)
  {
    return new lel::ecs::system::CoreCommands(proxy);
  }

  CORECOMMANDS_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}
