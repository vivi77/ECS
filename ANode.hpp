#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

namespace lel
{
  namespace graph
  {
    /** @brief Graph node
     *
     *  Update your data through the method 'getData()'
     */
    template <typename T>
    class ANode
    {
    public:
      using Data = T;
      using NodePtr = std::shared_ptr<ANode>;

    public:
      /** @brief Default constructor. Data assignable
       *
       *  @param data Optional. Value to set
       */
      ANode(const T& data = T{})
        : _linkedNodes{}
        , _data{data}
      {}

      /** @brief Constructor with children nodes
       *
       *  @param nodes Nodes to link to the created one
       */
      template <typename... Nodes>
      ANode(Nodes&&... nodes)
        : _linkedNodes{std::forward<Nodes>(nodes)...}
      {}

      /** @brief Constructor. Data and children assignable.
       *
       *  @param data Value to set
       *  @param nodes Nodes to link to the created one
       */
      template <typename... Nodes>
      ANode(const T& data, Nodes&&... nodes)
        : _linkedNodes{std::forward<Nodes>(nodes)...}
        , _data{data}
      {}

      ANode(const ANode&) = default;
      ANode(ANode&&) = default;
      virtual ~ANode() = default;

      ANode& operator=(const ANode&) = default;
      ANode& operator=(ANode&&) = default;

      /** @brief Get node data
       */
      // 01/03/2018: Is there a reason about why this is virtual ?
      virtual T& getData()
      {
        return _data;
      }

      /** @brief Set node data
       */
      void setData(const T& data) noexcept
      {
        _data = data;
      }

      /** @brief Indicates if the node is being computed
       */
      bool isComputing() const noexcept
      {
        return _computing;
      }

      /** @brief Indicates if the node has been computed
       */
      bool isComputed() const noexcept
      {
        return _computed;
      }

      /** @brief Get access to its linked nodes
       */
      const std::vector<NodePtr>& getLinkedNodes() const noexcept
      {
        return _linkedNodes;
      }

      /** @brief Execute a function on the node
       *
       *  @return A copy of the data after the function execution
       *
       *  @remarks This set a flag which indicates if the node has already been
       *  computed or not. When it has been computed, the function is not
       *  re-executed
       *  @remarks NVI function
       */
      T compute()
      {
        if (!isComputing() && !isComputed())
          {
            startComputing();
            doCompute();
            endComputing();
            computedDone();
          }
        else if (isComputed())
          whenComputed();
        return getData();
      }

      /** @brief Link the node with the given one
       *
       *  @param node A node
       *
       *  @return `true` is the node has been added. Else `false`
       */
      // Look comment at the bottom of the file to know why it is not const ref
      virtual bool link(NodePtr node)
      {
        auto beginIt = std::begin(_linkedNodes);
        auto endIt = std::end(_linkedNodes);
        auto it = std::find(beginIt, endIt, node);
        if (it != endIt)
          return false;
        _linkedNodes.emplace_back(node);
        return true;
      }

      /** @brief Unlink the node with the given one
       *
       *  @param node A linked node
       *
       *  @return `true` is the node has been removed. Else `false`
       */
      // Look comment at the bottom of the file to know why it is not const ref
      virtual bool unlink(NodePtr node)
      {
        auto beginIt = std::begin(_linkedNodes);
        auto endIt = std::end(_linkedNodes);
        auto it = std::find(beginIt, endIt, node);
        if (it == endIt)
          return false;
        _linkedNodes.erase(it);
        return true;
      }

      /** @brief Allow a node to be computed
       *
       *  @remarks NVI function
       */
      void resetComputed() noexcept
      {
        // Avoid infinite recursion/stack overflow
        if (!isComputed())
          return ;

        _computed = false;
        onResetComputed();
      }

    protected:
      /** @brief Get a total access to the linked nodes
       */
      std::vector<NodePtr>& accessLinkedNode() noexcept
      {
        return _linkedNodes;
      }

      const std::vector<NodePtr>& accessLinkedNode() const noexcept
      {
        return _linkedNodes;
      }

    private:
      std::vector<NodePtr> _linkedNodes; /**< Nodes linked to this one */
      bool                 _computing = false; /**< Flag which indicates if the node is being computed */
      bool                 _computed = false; /**< Flag which indicates if the node has been computed */
      T                    _data = T{}; /**< Data holded by the node */

      /** @brief Set up the flag of being computed
       */
      void startComputing() noexcept
      {
        _computing = true;
      }

      /** @brief Set down the flag of being computed
       */
      void endComputing() noexcept
      {
        _computing = false;
      }

      /** @brief Set up the flag of 'has been computed'
       */
      void computedDone() noexcept
      {
        _computed = true;
      }

      /** @brief Function which really do the reset
       */
      virtual void onResetComputed() noexcept
      {
        for (auto& it : _linkedNodes)
          it->resetComputed();
      }

      /** @brief Method called when 'compute' is called
       */
      virtual void doCompute() = 0;

      /** @brief Method called when 'compute' is called and the 'computed' flag is
       *  up
       */
      virtual void whenComputed() = 0;

      friend bool operator==(const std::shared_ptr<ANode>& lhs, const ANode& rhs)
      {
        return (&lhs.get() == &rhs);
      }
    };
  } /* !graph */
} /* !lel */

#if 0
Concerning the method 'link' and 'unlink'
  - As it is virtual, it can be redefined and the new definition may want to be
    able to modify it.
      ==> no const
  - As it is a shared_ptr it can be converted into an other shared_ptr, without
    cast the pointer through a new variable, only if there is no reference.
      ==> no ref
#endif
