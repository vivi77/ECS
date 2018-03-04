#pragma once

#include <string>
#include <vector>
#include <regex>

namespace ECS
{
  namespace Utility
  {
    class FileSearcher
    {
    public:
      void searchFile(const char* path, const std::regex&);
      void searchExtension(const char* path, const char* extension);

      template <typename Fct>
      void applyOnResult(Fct&& fct)
      {
        for (auto& path : _result)
          std::forward<Fct>(fct)(path);
      }

      template <typename T, typename Fct>
      std::vector<T> applyOnResult(Fct&& fct)
      {
        std::vector<T> result;

        for (auto& path : _result)
          result.emplace_back(std::forward<Fct>(fct)(path));

        return result;
      }

      std::vector<std::string> getResult() const
      {
        return _result;
      }

    public:
      static const char* DYNAMIC_LIBRARY_EXTENSION;

    private:
      std::vector<std::string> _result;
    };
  } /* !Utility */
} /* !ECS */
