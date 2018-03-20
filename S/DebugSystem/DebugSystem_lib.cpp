#include "DebugSystem.hh"
#include "S/DebugSystem/debugsystem_export.h"
#include "S/SIDGenerator.hh"
#include "S/S_lib.hh"

extern "C"
{
  DEBUGSYSTEM_EXPORT IS* create()
  {
    return new DebugSystem;
  }

  DEBUGSYSTEM_EXPORT void destroy(IS* ptr)
  {
    delete ptr;
  }
}

static void assignID()
{
  DebugSystem::assignID(SIDGenerator::getSingleton().generateID());
}

template struct EntryPointWrapper<DebugSystem>;
