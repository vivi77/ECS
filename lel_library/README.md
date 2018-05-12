# README

Lel's library

## CONTENTS

Standalone template classes:
- [ANode](ANode.md): Base class of a graph node. It can be computed even in a cyclic graph.
- [DLLoader](DLLoader.md): Policy-based dynamic library loader class.
- [Parser](Parser.md): Policy-based implementation of a Pratt parser. It can be used recursively with itself.
- [SafeQueue](SafeQueue.md): Simple implementation of a thread-safe queue.

Packages:
- [meta](meta.md): Contains metaprogramming utility classes.
- [OSDLLoader](OSDLLoader.md): Cross-platform dynamic library loader.
- [CLIParser](CLIParser.md): Command line interface parser using [Parser](Parser.md).
- [Log](Log.md): Simple log class. Log only when macros *DEBUG* or *_DEBUG* are defined.
- [Threadpool](Threadpool.md): Simple implementation of a thread pool.

## USAGE

Using CMake:
1) add_subdirectory the repository
2) Add to target_link_libraries() any of those values:
    - lel_lib to link the whole library (Standalone templates + Packages)
    - lel_utils to link against the standalone classes
    - Any package name