#include "CLI.hh"
#include "S/CLI/clisystem_export.h"

extern "C"
{
  CLISYSTEM_EXPORT lel::ecs::system::IS* create()
  {
    return new lel::ecs::system::CLI;
  }

  CLISYSTEM_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}
