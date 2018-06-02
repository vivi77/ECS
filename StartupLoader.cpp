#include "StartupLoader.hh"

namespace
{
  lel::ecs::StartupLoader::PathContainer retrieveSystemPaths(const std::string& filename)
  {
    std::ifstream f{filename};
    if (!f)
      return {};

    lel::ecs::StartupLoader::PathContainer paths;
    std::string path;
    while (std::getline(f, path))
      paths.emplace_back(path);
    return paths;
  }
} /* ! */

namespace lel::ecs
{
  StartupLoader::StartupLoader(const std::string& filename)
    : _paths{retrieveSystemPaths(filename)}
  {}
} /* !lel::ecs */
