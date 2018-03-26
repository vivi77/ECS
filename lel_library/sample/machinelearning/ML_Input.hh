#pragma once

#include "ML_ANode.hh"

namespace ml
{
  class Input : public ANode
  {
    using Super = ANode;

  public:
    Input(const std::string& name, const Data data);
    Input(const Input&) = default;
    Input(Input&&) = default;
    virtual ~Input() = default;

    Input& operator=(const Input&) = default;
    Input& operator=(Input&&) = default;

    /** @brief Override 'link' method inherited from ml::ANode
     *
     *  This definition refuse any link
     *
     *  @return Always `false`
     */
    bool link(NodePtr node) override;

  private:
    /** @brief Inherited from ml::ANode
     *
     *  This definition only display information
     */
    void doForwardPass(std::stringstream& ss) override;

    /** @brief Inherited from ml::ANode
     */
    void doBackPropagation(const double) override {}
  };
} /* !ml */
