#include "ML_Circuit.hh"

namespace ml
{
  //NamedInput
  Circuit::NamedInput::NamedInput(const std::string& name)
    : Super{name}
  {
    ;
  }

  bool Circuit::NamedInput::link(NodePtr node)
  {
    if (isLinked())
      {
        auto& refNode{accessLinkedNode()[0]};
        refNode.swap(node);
        return (true);
      }
    return (Super::link(node));
  }

  Data& Circuit::NamedInput::getData()
  {
    if (getLinkedNodes().empty())
      {
        std::string msg{__FUNCTION__};
        throw std::runtime_error{msg + ": Is linked with nothing"};
      }
    return (accessLinkedNode()[0]->getData());
  }

  void Circuit::NamedInput::doForwardPass(std::stringstream& ss)
  {
    ss << __PRETTY_FUNCTION__ << ": " << getData() <<"\n";
  }

  void Circuit::NamedInput::doBackPropagation(const double)
  {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }

  //CircuitNodeBuilder
  void Circuit::CircuitNodeBuilder::_addNoDupes(NodeNameContainer& container, const NodeName& name)
  {
    auto beginIt{std::begin(container)};
    auto endIt{std::end(container)};
    auto it{std::find(beginIt, endIt, name)};
    if (it == endIt)
      container.emplace_back(name);
  }

  void Circuit::CircuitNodeBuilder::_reset()
  {
    mInputs.clear();
    mOutputs.clear();
    mNamedInputs.clear();
    mIsStartNode = false;
  }

  //Circuit
  Circuit::Circuit(const std::string& name)
    : Super{name}
    , mInputs{}
    , mStartNode{nullptr}
  {
    ;
  }

  bool Circuit::addNamedInput(const std::string& name)
  {
    auto beginIt{std::begin(mInputs)};
    auto endIt{std::end(mInputs)};
    auto pred{[&name](const auto& it) -> bool
          {
            return (it->getName() == name);
          }};
    auto it{std::find_if(beginIt, endIt, pred)};
    if (it != endIt)
      return (false);
    auto ptr{std::make_shared<NamedInput>(name)};
    mInputs.emplace_back(ptr);
    return (true);
  }

  bool Circuit::link(NodePtr node)
  {
    auto beginIt{std::begin(mInputs)};
    auto endIt{std::end(mInputs)};
    auto pred{[](const auto& it) -> bool
          {
            return (!it->isLinked());
          }};
    auto it{std::find_if(beginIt, endIt, pred)};
    return (it == endIt ? false : ((*it)->link(node)));
  }

  bool Circuit::unlink(NodePtr node)
  {
    auto beginIt{std::begin(mInputs)};
    auto endIt{std::end(mInputs)};
    auto pred{[&node](const auto& it) -> bool
          {
            return (it->getLinkNode() == node);
          }};
    auto it{std::find_if(beginIt, endIt, pred)};
    return (it == endIt ? false : (*it)->unlink(node));
  }

  std::shared_ptr<Circuit::Super> Circuit::getNodeByName(const std::string& name)
  {
    auto beginIt{std::begin(mNodes)};
    auto endIt{std::end(mNodes)};
    auto pred{[&name](const auto& it) -> bool
          {
            return (it->getName() == name);
          }};
    auto it{std::find_if(beginIt, endIt, pred)};
    return (it != endIt ? *it : nullptr);
  }

  void Circuit::doForwardPass(std::stringstream& ss)
  {
    mStartNode->compute();
    ss << "Computing circuit\n";
  }

  void Circuit::doBackPropagation(const double stepSize)
  {
    std::cout << "Back propagating\n";
    mStartNode->backPropagate(stepSize);
  }

  void Circuit::onResetComputed() noexcept
  {
    for (auto& it : mNodes)
    {
      it->resetComputed();
    }
    for (auto& it : this->getLinkedNodes())
    {
      it->resetComputed();
    }
  }

  void Circuit::onResetBackPropagationFlag() noexcept
  {
    for (auto& it : mNodes)
    {
      it->resetBackPropagationFlag();
    }
    for (auto& it : this->getLinkedNodes())
    {
      std::static_pointer_cast<ml::ANode>(it)->resetBackPropagationFlag();
    }
  }
} /* !ml */
