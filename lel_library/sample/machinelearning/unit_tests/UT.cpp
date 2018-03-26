#include "gtest/gtest.h"
#include "ML_Input.hh"
#include "ML_Output.hh"

namespace
{
  auto checkStandalone{[](auto& node, const int line) { EXPECT_FALSE(node.isInputNode() || node.isOutputNode()) << "call line: " << line; }};
  auto checkInput{[](auto& node, const int line) { EXPECT_TRUE(node.isInputNode()) << "call line: " << line; EXPECT_FALSE(node.isOutputNode()) << "call line: " << line; }};
  auto checkOutput{[](auto& node, const int line) { EXPECT_FALSE(node.isInputNode()) << "call line: " << line; EXPECT_TRUE(node.isOutputNode()) << "call line: " << line; }};
  auto checkIO{[](auto& node, const int line) { EXPECT_TRUE(node.isInputNode() && node.isOutputNode()) << "call line: " << line; }};
} /* ! */

TEST(ANode, NodeType)
{
  std::shared_ptr<ml::ANode> i{std::make_shared<ml::Input>("i", ml::Data{0, 0})};
  ml::Output o1{"o1", i};

  checkInput(*i.get(), __LINE__);
  checkOutput(o1, __LINE__);

  ml::Output o2{"o2", i};
  ml::Output o3{"o3", i};

  o1.unlink(i);
  checkStandalone(o1, __LINE__);
  checkOutput(o2, __LINE__);
  checkOutput(o3, __LINE__);
  checkInput(*i.get(), __LINE__);

  o1.unlink(i);
  checkStandalone(o1, __LINE__);
  checkOutput(o2, __LINE__);
  checkOutput(o3, __LINE__);
  checkInput(*i.get(), __LINE__);

  o2.unlink(i);
  o3.unlink(i);
  checkStandalone(o2, __LINE__);
  checkStandalone(o3, __LINE__);
  checkStandalone(*i.get(), __LINE__);

  o2.link(i);
  checkInput(*i.get(), __LINE__);
  checkOutput(o2, __LINE__);
}
