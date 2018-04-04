#include "Debug.hh"
#include "S/Debug/debugsystem_export.h"
#include "S/SIDGenerator.hh"
#include "S/S_lib.hh"

extern "C"
{
  DEBUGSYSTEM_EXPORT lel::ecs::system::IS* create()
  {
    return new lel::ecs::system::Debug;
  }

  DEBUGSYSTEM_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}

static void assignID()
{
  //lel::ecs::system::Debug::assignID(lel::ecs::system::SIDGenerator::getSingleton().generateID());
}

template struct EntryPointWrapper<lel::ecs::system::Debug>;
