#pragma once

#include "ANode.hpp"
#include "ML_Data.hh"
#include <sstream>

namespace ml
{
  class ANode : public lel::graph::ANode<Data>
  {
  public:
    using Super = lel::graph::ANode<Data>;
    using BasePtr = std::shared_ptr<ANode>;

  public:
    // I prefer it than placing default parameter on 'data' of the 2nd ctor
    //   as Super already has default parameter on this member
    /** @brief Constructor. Give the node a name
     */
    ANode(const std::string& name);

    /** @brief Constructor. Take the name of the node and set its value
     */
    ANode(const std::string& name, const Data data);

    /** @brief Constructor. Give the node a name and link it with other
     *  nodes
     *
     *  @param nodes A variadic number of ml::ANode
     */
    template <typename ... Nodes>
    ANode(const std::string& name, Nodes&& ... nodes)
      : Super{std::forward<Nodes>(nodes)...}
      , mName{name}
      , mBackPropagated{false}
      , mBackPropagating{false}
      , mInputRef{0}
      , mOutput{false}
    {
      (nodes->upInputRef(), ...);
      updateOutputFlag();
    }

    /** @brief Constructor. Give the node a name, Set its data and link it with
     *  other nodes
     *
     *  @param nodes A variadic number of ml::ANode
     */
    template <typename ... Nodes>
    ANode(const std::string& name, const Data data, Nodes&& ... nodes)
      : Super{data, std::forward<Nodes>(nodes)...}
      , mName{name}
      , mBackPropagated{false}
      , mBackPropagating{false}
      , mInputRef{0}
      , mOutput{false}
    {
      (nodes->upInputRef(), ...);
      updateOutputFlag();
    }

    // Look at the bottom of the file to see why it is deleted
    ANode(const ANode&) = delete;
    ANode(ANode&&) = default;
    virtual ~ANode() = default;

    // Look at the bottom of the file to see why it is deleted
    ANode& operator=(const ANode&) = delete;
    ANode& operator=(ANode&&) = default;

    /** @brief Get node name
     */
    const std::string& getName() const noexcept
    {
      return (mName);
    }

    /** @brief Indicates if this node is used as an input
     */
    bool isInputNode() const noexcept
    {
      return (mInputRef != 0);
    }

    /** @brief Indicates if this node is used as an output
     */
    bool isOutputNode() const noexcept
    {
      return (mOutput);
    }

    /** @brief Launch machine learning back propagation system
     *
     *  @param stepSize Factor value applied to gradient. (Value destined to input nodes)
     */
    void backPropagate(const double stepSize) noexcept;

    /** @brief Set down the flag of backPropagation. Enable it to back propagate again
     */
    void resetBackPropagationFlag() noexcept;

    /** @brief Set up the flag of backPropagation.
     */
    void backPropagationDone() noexcept
    {
      mBackPropagated = true;
    }

    /** @brief Set up the flag of being back propagated
     */
    void startBackPropagation() noexcept
    {
      mBackPropagating = true;
      indent += 2;
    }

    /** @brief Set down the flag of being back propagated
     */
    void endBackPropagation() noexcept
    {
      indent -= 2;
      mBackPropagating = false;
    }

    /** @brief Overrided 'link' method inhertied from graph::ANode
     */
    bool link(NodePtr node) override;

    /** @brief Overrided 'unlink' method inhertied from graph::ANode
     */
    bool unlink(NodePtr node) override;

  private:
    std::string mName; /**< Node name */
    bool mBackPropagated; /**< Flag which indicates if the node has done the back propagation */
    bool mBackPropagating; /**< Flag which indicates if the node is being computed for back propagation */
    int mInputRef; /**< Indicates how many times the node is used as an input */
    bool mOutput; /**< Flag which indicates if the node is used as an output */
    static size_t indent; /**< For display */

    /** @brief Update data using a factor and the current gradient
     *
     *  @param stepSize Factor value applied to gradient. (Value destined to input nodes)
     *
     *  @remarks This method should be called when the node has no linked node
     *  (ie. input node)
     */
    void _updateData(const double stepSize) noexcept
    {
      std::cout << __PRETTY_FUNCTION__ << " " << getData() << "\n";
      getData().applyGradient(stepSize);
    }

    /** @brief Call 'backPropagate' of children nodes
     *
     *  @param stepSize Factor value applied to gradient. (Value destined to input nodes)
     */
    void _recBackPropagation(const double stepSize) noexcept;

    /** @brief Has done back propagation
     */
    bool isBackPropagated() const noexcept
    {
      return (mBackPropagated);
    }

    /** @brief Is doing back propagation
     */
    bool isBackPropagating() const noexcept
    {
      return (mBackPropagating);
    }

    /** @brief Update 'mOutput' flag
     */
    void updateOutputFlag() noexcept
    {
      mOutput = !getLinkedNodes().empty();
    }

    /** @brief Method called when the node is linked to an other one
     */
    void upInputRef() noexcept
    {
      ++mInputRef;
    }

    /** @brief Method called when the node is unlinked to an other one
     */
    void downInputRef() noexcept
    {
      if (mInputRef > 0)
        --mInputRef;
    }

    /** @brief Inherited from graph::ANode
     */
    void doCompute() final;

    /** @brief Inherited from graph::ANode
     */
    void whenComputed() final;

    /** @brief Complete the call to 'doCompute'
     */
    virtual void doForwardPass(std::stringstream&) = 0;

    /** @brief Do the backpropagation process
     *
     *  @param stepSize Factor value applied to gradient. (Value destined to input nodes)
     */
    virtual void doBackPropagation(const double stepSize) = 0;

    /** @brief Do the back propagation reset
     */
    virtual void onResetBackPropagationFlag() noexcept;
  };
} /* !ml */

#if 0
Actually copying nodes is forbidden because the copy operation have impact on some
attributes and because the effects of this operation has not been planned

4 types of node:
  standalone node: Node is not linked with a node nor has node linked to it
  input node: Node which is linked with at least one node
  output node: Node which has at least one node linked to it
  i/o node: Node with both characteristics of input and output node

  - Data representation:
    !Input && !Output => standalone node
     Input && !Output => input node
    !Input &&  Output => output node
     Input &&  Output => i/o node
#endif
