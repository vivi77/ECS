#include "CLISystem.hh"
#include "clisystem_export.h"
#include "S_lib.hh"
#include "SIDGenerator.hh"

static void assignID()
{
  CLISystem::assignID(SIDGenerator::getSingleton().generateID());
}

template struct EntryPointWrapper<CLISystem>;

extern "C"
{
  CLISYSTEM_EXPORT IS* create()
  {
    return new CLISystem;
  }

  CLISYSTEM_EXPORT void destroy(IS* ptr)
  {
    std::cout << "yolololo\n";
    delete ptr;
  }
}
