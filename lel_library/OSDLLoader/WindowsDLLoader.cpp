#ifdef _WIN32
#include "WindowsDLLoader.hh"

std::string _WindowsDLLoader::lastError;

_WindowsDLLoader::Handle _WindowsDLLoader::loadLibrary(const char* libPath)
{
  Handle handle = LoadLibrary(libPath);
  if (handle == NULL_HANDLE)
    lastError = std::system_category().default_error_condition(GetLastError()).message();
  return handle;
}

void _WindowsDLLoader::unloadLibrary(Handle handle)
{
  if (!FreeLibrary(handle))
    lastError = std::system_category().default_error_condition(GetLastError()).message();
}

_WindowsDLLoader::Symbol _WindowsDLLoader::getSymbol(Handle handle, const char* symName)
{
  Symbol symbol = GetProcAddress(handle, symName);
  if (symbol == nullptr)
    lastError = std::system_category().default_error_condition(GetLastError()).message();
  return symbol;
}

const char* _WindowsDLLoader::getLastError()
{
  return lastError.c_str();
}
#endif
