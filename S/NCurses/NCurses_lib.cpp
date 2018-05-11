#include "NCurses.hh"
#include "S/IS.hh"

extern "C"
{
  NCURSESSYSTEM_EXPORT lel::ecs::system::IS* create(lel::ecs::CoreProxy& proxy)
  {
    return new lel::ecs::system::NCurses(proxy);
  }

  NCURSESSYSTEM_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}
