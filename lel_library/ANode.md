# ANode

Base class of a graph node.

## Usage

The class ANode takes as template parameter the type of the data it will handle.
You will have to override these 2 virtual functions:

* `void doCompute()`: callback which is called when the node is computed
* `void whenComputed()`: callback which is called when the node is computed whereas it has already been computed

```
ANode* ptr = new GraphNode{12};
ANode* child = new GraphNode{24};
ANode* child2 = new GraphNode{48};

ptr->link(child);
child->link(child2);

std::cout << ptr->getData() << std::endl; // Output: 12
std::cout << child->getData() << std::endl; // Output: 24
ptr->compute(); // Exemple: Add the data of its child node
ptr->resetComputed();
std::cout << ptr->getData() << std::endl; // Output: 36 = 12 + 24
std::cout << child->getData() << std::endl; // Output: 72 = 24 + 48
```

## Public functions

Functions      | Descriptions
---------------|-----------------------------------------------------------------
compute        | Call the callback 'doCompute()' of this node and of its children
link           | Add a child to the caller node
unlink         | Remove a child to the caller node
resetComputed  | Reset to `false` the flag of `isComputed()` of this node and of its children
setData        | Change the data value
getData        | Retrieve the data
getLinkedNodes | Retrieve child nodes
isComputing    | Indicates if the node is in the call stack
isComputed     | Indicates if the node has been computed and/or not reseted
