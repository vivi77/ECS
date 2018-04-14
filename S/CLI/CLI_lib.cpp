#include "CLI.hh"
#include "S/CLI/clisystem_export.h"

extern "C"
{
  CLISYSTEM_EXPORT lel::ecs::system::IS* create(lel::ecs::CoreProxy* proxy)
  {
    std::unique_ptr<lel::ecs::CoreProxy> proxyPtr{proxy};
    return new lel::ecs::system::CLI(proxyPtr);
  }

  CLISYSTEM_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}
