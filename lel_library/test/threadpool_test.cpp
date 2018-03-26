#include "gtest/gtest.h"
#include "ThreadPool.hh"

TEST(ThreadPool, basicUsage)
{
  int i = 0;
  auto fct = [&i]() { ++i; };
  lel::ThreadPool t{5};
  for (int j = 0; j < 100; ++j)
    t.addOrder(fct);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  ASSERT_EQ(i, 100);
}
