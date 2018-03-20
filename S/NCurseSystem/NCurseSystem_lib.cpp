#include "NCurseSystem.hh"
#include "S/IS.hh"
#include "S/S_lib.hh"

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
