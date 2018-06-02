#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <experimental/filesystem>

namespace lel::ecs
{
  class StartupLoader
  {
  public:
    using Path = std::string;
    using PathContainer = std::vector<Path>;

  public:
    StartupLoader(const std::string& filename);
    template <typename Fct>
    void applyOnPaths(Fct&& fct)
    {
      for (std::experimental::filesystem::path p : _paths)
        std::forward<Fct>(fct)(p);
    }

  private:
    PathContainer _paths;
  };
} /* !lel::ecs */
