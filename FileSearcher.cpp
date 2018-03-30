#include "FileSearcher.hh"

namespace lel
{
  namespace utility
  {
#ifdef __linux__
    const char* FileSearcher::DYNAMIC_LIBRARY_EXTENSION = ".so";
#elif _WIN32
    const char* FileSearcher::DYNAMIC_LIBRARY_EXTENSION = ".dll";
#endif

    void FileSearcher::searchFile(const char* path, const std::regex& rg)
    {
      _result.clear();
      for (auto& it : std::experimental::filesystem::directory_iterator(path))
      {
        if (std::regex_match(it.path().filename().u8string(), rg))
        {
          _result.emplace_back(it.path());
        }
      }
    }

    void FileSearcher::searchExtension(const char* path, const char* extension)
    {
      _result.clear();
      for (auto& it : std::experimental::filesystem::directory_iterator(path))
      {
        if (it.path().extension() == extension)
        {
          _result.emplace_back(it.path());
        }
      }
    }
  } /* !utility */
} /* !lel */
