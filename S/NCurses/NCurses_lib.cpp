#include "NCurses.hh"
#include "S/IS.hh"

extern "C"
{
  NCURSESSYSTEM_EXPORT lel::ecs::system::IS* create(lel::ecs::CoreProxy* proxy)
  {
    std::unique_ptr<lel::ecs::CoreProxy> proxyPtr{proxy};
    return new lel::ecs::system::NCurses(proxyPtr);
  }

  NCURSESSYSTEM_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}
