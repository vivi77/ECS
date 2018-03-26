#pragma once
#ifdef _WIN32

#include "DLLoader.hpp"
#include <Windows.h>
#include <system_error>
#include <optional>

struct _WindowsDLLoader
{
  using Handle = HMODULE;
  using Symbol = FARPROC;

  static constexpr auto NULL_HANDLE = nullptr;
  static std::string lastError;

  static Handle loadLibrary(const char* libPath);

  static void unloadLibrary(Handle handle);

  static Symbol getSymbol(Handle handle, const char* symName);

  template <typename T>
  static T convertSymbol(Symbol sym)
  {
    return (T)sym;
  }

  static const char* getLastError();
};

using WindowsDLLoader = DLLoader<_WindowsDLLoader>;
#endif
