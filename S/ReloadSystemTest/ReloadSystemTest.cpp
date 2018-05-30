#include "ReloadSystemTest.hh"
#include <iostream>

ECS_CREATE_IDSYSTEM(ReloadSystemTest)

namespace lel::ecs::system
{
  ReloadSystemTest::ReloadSystemTest(CoreProxy& proxy)
    : CRTPS{proxy}
  {}

  void ReloadSystemTest::exec()
  {
    //std::cout << __FILE__ << "::" << __FUNCTION__ << "\n";
  }

  void ReloadSystemTest::registerEntity(const EntityPtr&)
  {
    //std::cout << __FILE__ << "::" << __FUNCTION__ << "\n";
  }

  void ReloadSystemTest::deregisterEntity(const EntityPtr&)
  {
    std::cout << __FILE__ << "::" << __FUNCTION__ << "\n";
  }

  void ReloadSystemTest::setup()
  {
    std::cout << __FILE__ << "::" << __FUNCTION__ << "\n";
  }

  void ReloadSystemTest::atRemove()
  {
    std::cout << __FILE__ << "::" << __FUNCTION__ << "\n";
  }
} /* !lel::ecs::system */
