#include "CLI.hh"
#include "S/S_lib.hh"
#include "S/SIDGenerator.hh"
#include "S/CLI/clisystem_export.h"

static void assignID()
{
  using namespace lel::ecs::system;

  CLI::assignID(SIDGenerator::getSingleton().generateID());
}

template struct EntryPointWrapper<lel::ecs::system::CLI>;

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
