#include "NCursesSystem.hh"
#include "S/IS.hh"
#include "S/S_lib.hh"
#include "S/SIDGenerator.hh"

extern "C"
{
  IS* create()
  {
    return new NCursesSystem();
  }

  void destroy(IS* ptr)
  {
    delete ptr;
  }
}

void assignID()
{
  NCursesSystem::assignID(SIDGenerator::getSingleton().generateID());
}

template struct EntryPointWrapper<NCursesSystem>;
