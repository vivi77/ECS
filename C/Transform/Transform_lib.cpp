#include "Transform.hh"
#include "C/C_lib.hh"
#include "C/CIDGenerator.hh"
#include "C/CManager/CManager.hh"

namespace
{
  void destroy(lel::ecs::component::IC* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  using Transform = lel::ecs::component::Transform;
  using CManager = lel::ecs::component::CManager;

  Transform::assignID(lel::ecs::component::CIDGenerator::getSingleton().generateID());
  CManager::registerCompDtor(Transform::getComponentID(), (CManager::Dtor)&::destroy);
}

template struct EntryPointWrapper<lel::ecs::component::Transform>;
