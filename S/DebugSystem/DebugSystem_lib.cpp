#include "DebugSystem.hh"
#include "debugsystem_export.h"
#include "SIDGenerator.hh"
#include "S_lib.hh"
#include "CManager.hh"

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
