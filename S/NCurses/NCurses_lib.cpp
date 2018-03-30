#include "NCurses.hh"
#include "S/IS.hh"
#include "S/S_lib.hh"
#include "S/SIDGenerator.hh"

extern "C"
{
  lel::ecs::system::IS* create()
  {
    return new lel::ecs::system::NCurses();
  }

  void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}

void assignID()
{
  lel::ecs::system::NCurses::assignID(lel::ecs::system::SIDGenerator::getSingleton().generateID());
}

template struct EntryPointWrapper<lel::ecs::system::NCurses>;
