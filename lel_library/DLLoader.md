# DLLoader

Policy-based class dynamic library loader class.

# Usage

Create a structure (or class) which respect the concept class *DLLoader_concept*
It must have the following characteristics:

  - 3 types named *Handle*, *Symbol* and *LoadOption*
    * Handle: It should be the type of your API shared library *handle*
    * Symbol: It should be the type of your API shared library *symbol*
    * LoadOption: If your API propose some options, set the type of theses options here
  - 1 static variable named NULL_HANDLE which should be the value of an invalid handle
  - 5 static methods:
    * loadLibrary: Your API function to *load* a shared library
    * unloadLibrary: Your API function to *unload* a shared library
    * getSymbol: Your API function to retrieve symbol from a shared library
    * getLastError: Your API function to retrieve the last error encoutered
    * isLibraryLoaded: How with your API you know if a library is already loaded

Then create a type alias using *DLLoader* and your structure, like this:
  `using <newLoaderName> = lel::DLLoader<YourStruct>;`
