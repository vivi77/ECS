#pragma once

#include "ML_ANode.hh"

namespace ml
{
  class Output : public ANode
  {
    using Super = ANode;

  public:
    Output(const std::string& name);
    Output(const std::string& name, BasePtr input);
    Output(const Output&) = default;
    Output(Output&&) = default;
    virtual ~Output() = default;

    Output& operator=(const Output&) = default;
    Output& operator=(Output&&) = default;

    /** @brief Override 'link' method inherited from ml::ANode
     */
    bool link(NodePtr node) override;

  private:
    void doForwardPass(std::stringstream& ss) override;
    void doBackPropagation(const double) override;
  };
} /* !ml */
