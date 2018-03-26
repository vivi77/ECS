#include "ML_Output.hh"

namespace ml
{
  Output::Output(const std::string& name)
    : Super{name}
  {
    ;
  }

  Output::Output(const std::string& name, BasePtr input)
    : Super{name, input}
  {
    ;
  }

  bool Output::link(NodePtr node)
  {
    if (getLinkedNodes().size() > 0)
      return (false);
    return (Super::link(node));
  }

  void Output::doForwardPass(std::stringstream& ss)
  {
    auto& input{getLinkedNodes().back()};

    ss << __PRETTY_FUNCTION__ << ": ";
    input->compute();
    setData(input->getData());
    ss << getData() << "\n";
  }

  void Output::doBackPropagation(const double)
  {
    // Simply forward the gradient it has
    auto& input{getLinkedNodes().back()};
    input->getData().setGradient(getData().getGradient());
    std::cout << __PRETTY_FUNCTION__ << ": " << getData() << "\n";
  }
} /* !ml */
