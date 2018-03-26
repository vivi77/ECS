#include "ANode.hpp"
#include "ML_ANode.hh"
#include "ML_Output.hh"
#include "ML_Input.hh"
#include "ML_Circuit.hh"
#include <string>
#include <memory>
#include <sstream>

namespace ml
{
  class BinaryMulGate : public ANode
  {
    using Super = ANode;

  public:
    BinaryMulGate(const std::string& name, BasePtr& lhs, BasePtr& rhs)
      : Super{name, lhs, rhs}
    {
      ;
    }
    BinaryMulGate(const BinaryMulGate&) = default;
    BinaryMulGate(BinaryMulGate&&) = default;
    virtual ~BinaryMulGate() = default;

    BinaryMulGate& operator=(const BinaryMulGate&) = default;
    BinaryMulGate& operator=(BinaryMulGate&&) = default;

  private:
    void doForwardPass(std::stringstream& ss) override
    {
      auto& lhs{getLinkedNodes()[0]};
      auto& rhs{getLinkedNodes()[1]};

      ss << __PRETTY_FUNCTION__ << ": Multiplying input: ";
      lhs->compute();
      rhs->compute();
      setData(lhs->getData() * rhs->getData());
      ss << getData() << "\n";
    }

    void doBackPropagation(const double) override
    {
      auto& lhs{getLinkedNodes()[0]};
      auto& rhs{getLinkedNodes()[1]};
      lhs->getData().setGradient(rhs->getData().getValue() * this->getData().getGradient());
      rhs->getData().setGradient(lhs->getData().getValue() * this->getData().getGradient());
      std::cout << __PRETTY_FUNCTION__ << " " << getData() << "\n";
    }
  };

  class Clock : public ANode
  {
  public:
    Clock(const std::string& name, const Data d1, const Data d2)
      : ANode{name}
      , mD1{d1}
      , mD2{d2}
    {
      ;
    }
    Clock(const Clock&) = default;
    Clock(Clock&&) = default;
    virtual ~Clock() = default;

    Clock& operator=(const Clock&) = default;
    Clock& operator=(Clock&&) = default;

  private:
    Data mD1;
    Data mD2;

    void doForwardPass(std::stringstream& ss) override
    {
      ss << __PRETTY_FUNCTION__ << ": Automatic input switcher: ";
      setData(getData() == mD1 ? mD2 : mD1);
      ss << getData() << "\n";
    }

    void doBackPropagation(const double) override
    {
      std::cout << __PRETTY_FUNCTION__ << " " << getData() << "\n";
    }
  };

  class AddGate : public ANode
  {
    using Super = ANode;

  public:
    template <typename ... Nodes>
    AddGate(const std::string& name, Nodes&& ... nodes)
      : Super{name, std::forward<Nodes>(nodes)...}
    {
      ;
    }
    AddGate(const AddGate&) = default;
    AddGate(AddGate&&) = default;
    virtual ~AddGate() = default;

    AddGate& operator=(const AddGate&) = default;
    AddGate& operator=(AddGate&&) = default;

    void doForwardPass(std::stringstream& ss) override
    {
      Data res{0, 0};

      ss << __PRETTY_FUNCTION__ << ": Adding input: ";
      for (auto& it : getLinkedNodes())
        {
          it->compute();
          res += it->getData();
        }
      setData(res);
      ss << getData() << "\n";
    }

    void doBackPropagation(const double) override
    {
      for (auto& it : getLinkedNodes())
        {
          it->getData().setGradient(1 * this->getData().getGradient());
        }
      std::cout << __PRETTY_FUNCTION__ << " " << getData() << "\n";
    }
  };
} /* !machineLearning */

template <typename ... Args>
void loop(Args&& ... args)
{
  std::cout << "Start loop\n";
  (std::forward<Args>(args).compute(), ...);
  std::cout << "End loop\n";
}

int main(void)
{
  auto c{std::make_shared<ml::Circuit>("c")};
  auto builder{c->buildNode()};
  auto i1{builder.createNode<ml::Input>("i1", ml::Data{31, 0})};
  auto i2{builder.createNode<ml::Input>("i2", ml::Data{11, 0})};
  auto c3{builder.createNode<ml::Clock>("c3", ml::Data{100, 0}, ml::Data{42, 0})};
  auto mul1{builder.createNode<ml::BinaryMulGate>("binMul1", i1, i2)};
  auto mul2{builder.createNode<ml::BinaryMulGate>("binMul2", mul1, c3)};
  auto o1{builder.setAsStartNode().createNode<ml::Output>("o1", mul1)};
  builder.createNode<ml::Output>("o2", mul2);
  builder.createNode<ml::Output>("o3", c3);
  builder.createNode<ml::AddGate>("add3", i1, i2, c3);
  c->compute();

  auto c1{std::make_shared<ml::Circuit>("c1")};
  auto c1Builder{c1->buildNode()};
  auto i4{c1Builder.createNode<ml::Input>("i4", ml::Data{500, 0})};
  auto c1add{c1Builder.createNode<ml::AddGate>("add", mul1, mul2, i4)};
  c1Builder.setAsStartNode().createNode<ml::Output>("o4", c1add);
  c1->compute();

  std::cout << "\n";
  auto& newData{o1->getData()};
  newData.setGradient(1.0f);
  c->backPropagate(0.1f);
  return (0);
}
