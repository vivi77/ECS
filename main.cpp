#include "Core.hh"
#include <iostream>

int main()
{
  try
  {
    auto core = std::make_shared<lel::ecs::Core>();

    core->run();
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
  }
  return (0);
}
