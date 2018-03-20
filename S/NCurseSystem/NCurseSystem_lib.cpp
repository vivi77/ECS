#include "NCurseSystem.hh"
#include "S/IS.hh"
#include "S/S_lib.hh"
#include "S/SIDGenerator.hh"

extern "C"
{
  IS* create()
  {
    return new NCurseSystem();
  }

  void destroy(IS* ptr)
  {
    delete ptr;
  }
}

void assignID()
{
  NCurseSystem::assignID(SIDGenerator::getSingleton().generateID());
}

template struct EntryPointWrapper<NCurseSystem>;
