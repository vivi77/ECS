#include "Debug.hh"
#include "S/Debug/debugsystem_export.h"

extern "C"
{
  DEBUGSYSTEM_EXPORT lel::ecs::system::IS* create(lel::ecs::CoreProxy& proxy)
  {
    return new lel::ecs::system::Debug(proxy);
  }

  DEBUGSYSTEM_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}
