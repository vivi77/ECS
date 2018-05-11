#include "CLI.hh"
#include "S/CLI/clisystem_export.h"

extern "C"
{
  CLISYSTEM_EXPORT lel::ecs::system::IS* create(lel::ecs::CoreProxy& proxy)
  {
    return new lel::ecs::system::CLI(proxy);
  }

  CLISYSTEM_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}
