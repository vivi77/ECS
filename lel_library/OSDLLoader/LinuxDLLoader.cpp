#ifdef __linux__
#include "LinuxDLLoader.hh"

namespace lel
{
  const char* _LinuxDLLoader::lastError = nullptr;

  _LinuxDLLoader::Handle _LinuxDLLoader::loadLibrary(const char* libPath, const LoadOption option) noexcept
  {
    lastError = nullptr;
    Handle tmp = dlopen(libPath, option);
    lastError = dlerror();
    return tmp;
  }

  void _LinuxDLLoader::unloadLibrary(Handle handle) noexcept
  {
    lastError = nullptr;
    dlclose(handle);
    lastError = dlerror();
  }

  _LinuxDLLoader::Symbol _LinuxDLLoader::getSymbol(Handle handle, const char* symName) noexcept
  {
    lastError = nullptr;
    //Few chance to get into this part of code when used with DLLoader<>
    if (handle == NULL_HANDLE)
      return nullptr;
    dlerror();
    Symbol tmp = dlsym(handle, symName);
    lastError = dlerror();
    return tmp;
  }

  const char* _LinuxDLLoader::getLastError()
  {
    return lastError;
  }

  bool _LinuxDLLoader::isLibraryLoaded(const char* libPath) noexcept
  {
    Handle tmp = dlopen(libPath, RTLD_NOLOAD);
    return tmp != nullptr;
  }
} /* !lel */
#endif
