#include "CLISystem.hh"
#include "S/S_lib.hh"
#include "S/SIDGenerator.hh"
#include "S/CLISystem/clisystem_export.h"

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
    delete ptr;
  }
}
