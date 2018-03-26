#include "gtest/gtest.h"
#include "OSDLLoader.hh"
#include "conditional_os.hpp"

TEST(OSDLLoader, BasicUsage)
{
  lel::meta::conditional_os<const char*> path("/home/le_l/workspace/lel_library/test/libtest.so", "../../test/test.dll");
  lel::OSDLLoader l{path.value};
  ASSERT_TRUE(l.isValid());
  EXPECT_EQ(l.countUsage(), 1);

  auto fct = l.getSymbol<int(*)(const int, const int)>("add");
  ASSERT_TRUE(fct.isValid());
  EXPECT_EQ(fct(1, 2), 3);

  auto var = l.getSymbol<int>("global_value");
  ASSERT_TRUE(var.isValid());
  int v = var;
  EXPECT_EQ(v, 42);

  l.unloadLibrary();
  ASSERT_FALSE(l.isValid());
  EXPECT_EQ(l.countUsage(), 0);
}

TEST(OSDLLoader, ErrorHandling)
{
  lel::OSDLLoader l{"asfd"};
  ASSERT_FALSE(l.isValid());
  ASSERT_NE(l.getLastError(), nullptr);
  ASSERT_FALSE(l.getSymbol<int>("toto").isValid());
}

TEST(OSDLLoader, concept)
{
  auto v = lel::concept::DLLoader<lel::_LinuxDLLoader, false>::value;
  ASSERT_TRUE(v);
  v = lel::concept::DLLoader<std::string, false>::value;
  ASSERT_FALSE(v);
}
