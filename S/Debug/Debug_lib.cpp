#include "Debug.hh"
#include "S/Debug/debugsystem_export.h"

extern "C"
{
  DEBUGSYSTEM_EXPORT lel::ecs::system::IS* create(lel::ecs::CoreProxy* proxy)
  {
    std::unique_ptr<lel::ecs::CoreProxy> proxyPtr{proxy};
    return new lel::ecs::system::Debug(proxyPtr);
  }

  DEBUGSYSTEM_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}
