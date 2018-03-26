#include "ML_Input.hh"

namespace ml
{
  Input::Input(const std::string& name, const Data data)
    : Super{name, data}
  {
    ;
  }

  bool Input::link(NodePtr)
  {
    return (false);
  }

  void Input::doForwardPass(std::stringstream& ss)
  {
    ss << __PRETTY_FUNCTION__ << ": " << getData() << "\n";
  }
} /* !ml */
