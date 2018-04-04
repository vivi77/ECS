#include "NCurses.hh"
#include "S/IS.hh"
#include "S/S_lib.hh"
#include "S/SIDGenerator.hh"
#include "C/CIDGenerator.hh"
#include "C/CManager/CManager.hh"

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

namespace
{
  void destroyNCTransform(lel::ecs::system::NCurses::NCTransform* ptr)
  {
    delete ptr;
  }
} /* ! */

void assignID()
{
  using namespace lel::ecs;

  //system::NCurses::assignID(system::SIDGenerator::getSingleton().generateID());
  //system::NCurses::NCTransform::assignID(component::CIDGenerator::getSingleton().generateID());
  //std::cout << system::NCurses::NCTransform::getComponentID() << " NCT\n";
  //component::CManager::registerCompDtor(system::NCurses::NCTransform::getComponentID(),
                                        //(component::CManager::Dtor)&::destroyNCTransform);
}

template struct EntryPointWrapper<lel::ecs::system::NCurses>;
