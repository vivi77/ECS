#include "ReloadSystemTest.hh"
#include "S/ReloadSystemTest/reloadsystemtest_export.h"
#include <iostream>

extern "C"
{
  RELOADSYSTEMTEST_EXPORT lel::ecs::system::IS* create(lel::ecs::CoreProxy& proxy)
  {
    std::cout << __FILE__ << "::" << __FUNCTION__ << " ---qwer qw\n";
    return new lel::ecs::system::ReloadSystemTest(proxy);
  }

  RELOADSYSTEMTEST_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    std::cout << __FILE__ << "::" << __FUNCTION__ << "\n";
    delete ptr;
  }
}

__attribute__((constructor))
void RSTentrypoint()
{
  std::cout << __FILE__ << "::" << __FUNCTION__ << "-----\n";
  std::cout << "\033[31mHello World !\033[0m\n";
}

__attribute__((destructor))
void RSTexitpoint()
{
  std::cout << __FILE__ << "::" << __FUNCTION__ << "\n";
}
