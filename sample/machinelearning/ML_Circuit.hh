#pragma once

#include "ML_Output.hh"

namespace ml
{
  /** @brief Class which handle a set of nodes
   */
  class Circuit : public ANode
  {
    using Super = ANode;
    using NodeContainer = std::vector<std::shared_ptr<Super>>;

    /** @brief Class which forward any data from a node to an other
     *
     *  It is used as a 'specific-named' node in Circuit class to identify
     *  entry points in the circuit
     */
    class NamedInput : public ANode
    {
      using Super = ANode;

    public:
      NamedInput(const std::string& name);
      NamedInput(const NamedInput&) = default;
      NamedInput(NamedInput&&) = default;
      virtual ~NamedInput() = default;

      NamedInput& operator=(const NamedInput&) = default;
      NamedInput& operator=(NamedInput&&) = default;

      /** @brief Indicates if the node is already linked
       */
      bool isLinked() const noexcept
      {
        return (!getLinkedNodes().empty());
      }

      /** @brief Get the only link node of this class
       */
      decltype(auto) getLinkNode() const noexcept
      {
        return (isLinked() ? getLinkedNodes()[0] : nullptr);
      }

      /** @brief Inherited from graph::ANode
       *
       *  This overrided method limits to 1 the number of linked node.
       *  It swap the old linked node with the new node if there is already one
       */
      bool link(NodePtr node) override;

      /** @brief Inherited from graph::ANode
       *
       *  This overrided method forward the data of its linked node
       *  It throws std::runtime_error if no node is linked with it
       */
      Data& getData() override;

      /** @brief Inherited from ANode
       */
      void doForwardPass(std::stringstream& ss) override;

      /** @brief Inherited from ANode
       */
      void doBackPropagation(const double) override;
    };

    /** @brief Node builder for a circuit
     */
    class CircuitNodeBuilder
    {
      using NodeName = std::string;
      using NodeNameContainer = std::vector<NodeName>;

    public:
      CircuitNodeBuilder(NodeContainer& nodes,
                         std::shared_ptr<Circuit::Super>& output,
                         std::vector<std::shared_ptr<NamedInput>>& inputs)
        : rCircuitNodes{nodes}
        , rCircuitOutput{output}
        , rCircuitInputs{inputs}
        , mInputs{}
        , mOutputs{}
        , mNamedInputs{}
        , mIsStartNode{false}
      {
        ;
      }

      CircuitNodeBuilder(const CircuitNodeBuilder&) = default;
      CircuitNodeBuilder(CircuitNodeBuilder&&) = default;
      ~CircuitNodeBuilder() = default;

      CircuitNodeBuilder& operator=(const CircuitNodeBuilder&) = default;
      CircuitNodeBuilder& operator=(CircuitNodeBuilder&&) = default;

      /** @brief Create a node in the circuit the builder is associated
       *
       *  @param name Name of the new node
       *
       *  @return `true` if the node has been created and inserted in the
       *  circuit
       *
       *  @remarks After the call, all data are cleared so the object can be
       *  reuse
       */
      template <typename NodeType, typename ... Args>
      std::shared_ptr<Super> createNode(Args&& ... args)
      {
        // No use of 'auto' to avoid implementation specificities of 'NodeType'
        // class
        std::shared_ptr<Super> newNode{std::make_shared<NodeType>(std::forward<Args>(args)...)};

        for (auto& outputName : mOutputs)
          {
            auto res{findNode(rCircuitNodes, outputName)};
            if (res == nullptr)
              continue;
            res->link(newNode);
          }
        for (auto& inputName : mInputs)
          {
            auto res{findNode(rCircuitNodes, inputName)};
            if (res == nullptr)
              continue;
            newNode->link(res);
          }
        for (auto& inputName : mNamedInputs)
          {
            auto res{findNode(rCircuitInputs, inputName)};
            if (res == nullptr)
              continue;
            newNode->link(res);
          }

        if (mIsStartNode)
          rCircuitOutput = newNode;

        rCircuitNodes.emplace_back(newNode);
        _reset();
        return (newNode);
      }

      /** @brief Decide that the next new node will be the circuit output
       */
      CircuitNodeBuilder& setAsStartNode() noexcept
      {
        mIsStartNode = true;
        return (*this);
      }

      /** @brief Add the node named 'name' as an output of the new node
       *
       *  @param name Name of a created node
       */
      CircuitNodeBuilder& addOutput(const std::string& name)
      {
        _addNoDupes(mOutputs, name);
        return (*this);
      }

      /** @brief Add the node named 'name' as an input of the new node
       *
       *  @param name Name of a create node
       */
      CircuitNodeBuilder& addInput(const std::string& name)
      {
        _addNoDupes(mInputs, name);
        return (*this);
      }

      /** @brief Add the NamedInput node named 'name' as an input of the new
       *  node
       *
       *  The difference between 'addInput' and this method is that an
       *  NamedInput is a node which will forward the data of any other node
       *  which can be link to the circuit whereas a classic node has a static
       *  data
       */
      CircuitNodeBuilder& addNamedInput(const std::string& name)
      {
        _addNoDupes(mNamedInputs, name);
        return (*this);
      }

    private:
      NodeContainer& rCircuitNodes;
      std::shared_ptr<Circuit::Super>& rCircuitOutput;
      std::vector<std::shared_ptr<NamedInput>>& rCircuitInputs;
      NodeNameContainer mInputs;
      NodeNameContainer mOutputs;
      NodeNameContainer mNamedInputs;
      bool mIsStartNode;

      /** @brief Add 'name' into 'container' if it does not exists
       *
       *  @param container A container of node names
       *  @param name A name to add
       */
      static void _addNoDupes(NodeNameContainer& container, const NodeName& name);

      /** @brief Clear all temporary data
       */
      void _reset();
    };

  public:
    /** @brief Constructor. Take the name of the circuit
     *
     *  @param name Name of the circuit
     */
    Circuit(const std::string& name);
    Circuit(const Circuit&) = default;
    Circuit(Circuit&&) = default;
    virtual ~Circuit() = default;

    Circuit& operator=(const Circuit&) = default;
    Circuit& operator=(Circuit&&) = default;

    /** @brief Add a named input in the circuit
     *
     *  @param name Name of the input
     *
     *  @return `true` if it is created, else `false` if it is already created
     */
    bool addNamedInput(const std::string& name);

    /** @brief Inherited from graph::ANode
     *
     *  This overrided method looks into the array of NamedInput nodes in the
     *  circuit and assign the node to the first one not linked
     *
     *  @return In addition of other errors from NamedInput::link (used in this
     *  method), it can return `false` when there is no more NamedInput
     *
     */
    bool link(NodePtr node) override;

    /** @brief Inherited from graph::ANode
     *
     *  This overrided method looks into the array of NamedInput nodes
     */
    bool unlink(NodePtr node) override;

    /** @brief Find a node in an array of nodes
     *
     *  @param circuitNodes An array of nodes from a Circuit class
     *  @param name Name of the node to search
     *
     *  @return On success, a pointer on the node, else nullptr
     */
    template <typename TNodeContainer>
    static std::shared_ptr<Super> findNode(const TNodeContainer& circuitNodes,
                                           const std::string& name)
    {
      auto beginIt{std::begin(circuitNodes)};
      auto endIt{std::end(circuitNodes)};
      auto pred{[&name](const auto& it) -> bool
            {
              return (it->getName() == name);
            }};
      auto it{std::find_if(beginIt, endIt, pred)};
      return (it == endIt ? nullptr : *it);
    }

    /** @brief Get a node from the circuit
     *
     *  @param name The name of search node
     *
     *  @return The wanted node, on success. On error, nullptr
     */
    std::shared_ptr<Super> getNodeByName(const std::string& name);

    /** @brief Create a class which create nodes in the circuit
     */
    CircuitNodeBuilder buildNode() noexcept
    {
      return CircuitNodeBuilder{mNodes, mStartNode, mInputs};
    }

  private:
    NodeContainer mNodes; /**< Circuit nodes */
    std::vector<std::shared_ptr<NamedInput>> mInputs; /**< Circuit inputs */
    std::shared_ptr<Super> mStartNode; /**< Circuit output node */

    /** @brief Inherited from ANode
     */
    void doForwardPass(std::stringstream& ss) override;

    /** @brief Inherited from ANode
     */
    void doBackPropagation(const double stepSize) override;

    /** @brief Inherited from ANode
     */
    void onResetComputed() noexcept override;

    /** @brief Inherited from ANode
     */
    void onResetBackPropagationFlag() noexcept override;
  };
} /* !ml */
