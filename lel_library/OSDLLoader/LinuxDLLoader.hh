#pragma once
#ifdef __linux__

#include "DLLoader.hpp"
#include <dlfcn.h>

namespace lel
{
  struct _LinuxDLLoader
  {
    using Handle = void*;
    using Symbol = void*;
    using LoadOption = int;

    static constexpr Handle NULL_HANDLE = nullptr;
    static const char* lastError;

    /** @brief Load a dynamic library
     *
     *  @param libPath Path to a dynamic library
     *  @param option Option to send to the loader
     *
     *  @return On success, a handle on the library. On error, NULL_HANDLE
     */
    static Handle loadLibrary(const char* libPath, const LoadOption option = RTLD_NOW) noexcept;

    /** @brief Unload a dynamic library
     *
     *  @param handle A handle on a dynamic library to close
     */
    static void unloadLibrary(Handle handle) noexcept;

    /** @brief Get a symbol from a handle
     *
     *  @param handle A handle on a dynamic library
     *  @param symName Symbol name
     *
     *  @return A symbol and the validity of this symbol.
     */
    static Symbol getSymbol(Handle handle, const char* symName) noexcept;

    /** @brief Convert a symbol to any type
     *
     *  @param sym A symbol
     *
     *  @return A converted symbol
     */
    template <typename T>
    static T convertSymbol(Symbol sym)
    {
      if constexpr (std::is_pointer_v<T>)
        return ((T)sym);
      else
        return (*(T*)sym);
    }

    /** @brief Get the last that occured with this library
     *
     *  @return A string with the last reported
     */
    static const char* getLastError();

    /** @brief Check if a library is already loaded.
     *
     *  @param libPath Path to a library.
     *
     *  @return true if the library is loaded
     */
    static bool isLibraryLoaded(const char* libPath) noexcept;
  };
  using LinuxDLLoader = DLLoader<_LinuxDLLoader>;
} /* !lel */
#endif
