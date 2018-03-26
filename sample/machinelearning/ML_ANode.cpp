#include "ML_ANode.hh"
#include <iostream>

namespace ml
{
  size_t ANode::indent{0};

  ANode::ANode(const std::string& name)
    : Super{}
    , mName{name}
    , mBackPropagated{false}
    , mBackPropagating{false}
    , mInputRef{0}
    , mOutput{false}
  {
    ;
  }

  ANode::ANode(const std::string& name, const Data data)
    : Super{data}
    , mName{name}
    , mBackPropagated{false}
    , mBackPropagating{false}
    , mInputRef{0}
    , mOutput{false}
  {
    ;
  }

  void ANode::backPropagate(const double stepSize) noexcept
  {
    // Do nothing if the back propagation is already done
    // Or if it will be done
    if (isBackPropagated() || isBackPropagating())
      {
        if (isBackPropagated())
          whenComputed();
        return ;
      }

    // Do back propagation for itself
    std::cout << std::string(indent, ' ') << mName << ": ";
    startBackPropagation();
    doBackPropagation(stepSize);
    backPropagationDone();
    if (!getLinkedNodes().empty())
      _recBackPropagation(stepSize);
    else
      _updateData(stepSize);
    endBackPropagation();
  }

  void ANode::resetBackPropagationFlag() noexcept
  {
    // Avoid infinte recursion loop/stack overflow
    if (!isBackPropagated())
      return ;
    mBackPropagated = false;
    onResetBackPropagationFlag();
  }

  bool ANode::link(NodePtr node)
  {
    if (!Super::link(node))
      return (false);
    std::static_pointer_cast<ANode>(node)->upInputRef();
    updateOutputFlag();
    return (true);
  }

  bool ANode::unlink(NodePtr node)
  {
    if (!Super::unlink(node))
      return (false);
    std::static_pointer_cast<ANode>(node)->downInputRef();
    updateOutputFlag();
    return (true);
  }

  void ANode::_recBackPropagation(const double stepSize) noexcept
  {
    for (auto& tmp : getLinkedNodes())
      {
        auto it{std::static_pointer_cast<ANode>(tmp)};
        it->backPropagate(stepSize);
      }
  }

  void ANode::onResetBackPropagationFlag() noexcept
  {
    for (auto& tmp : getLinkedNodes())
      {
        auto it{std::static_pointer_cast<ANode>(tmp)};
        it->resetBackPropagationFlag();
      }
  }

  void ANode::doCompute()
  {
    // Because of recursion to have a good display it is better to store data
    // and display data at the end of the computation
    std::stringstream ss;

    ss << std::string(indent, ' ') << mName << ": ";
    indent += 2;
    doForwardPass(ss);
    indent -= 2;
    std::cout << ss.str();
  }

  void ANode::whenComputed()
  {
    std::cout << std::string(indent, ' ') << mName << ": ";
    std::cout << __PRETTY_FUNCTION__ << ": " << getData() << " (Cached)\n";
  }
} /* !ml */
