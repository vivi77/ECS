#include "Transform.hh"
#include "C/C_lib.hh"
#include "C/CIDGenerator.hh"
#include "C/CManager/CManager.hh"

namespace
{
  void destroy(IC* ptr)
  {
    delete ptr;
  }
} /* ! */

static void setup()
{
  Transform::assignID(CIDGenerator::getSingleton().generateID());
  CManager::registerCompDtor(Transform::getComponentID(), (CManager::Dtor)&::destroy);
}

template struct EntryPointWrapper<Transform>;
