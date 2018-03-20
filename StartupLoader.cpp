#include "StartupLoader.hh"

namespace
{
  StartupLoader::PathContainer retrieveSystemPaths(const std::string& filename)
  {
    std::ifstream f{filename};
    if (!f)
      return {};

    StartupLoader::PathContainer paths;
    std::string path;
    while (std::getline(f, path))
      paths.emplace_back(path);
    return paths;
  }
} /* ! */

StartupLoader::StartupLoader(const std::string& filename)
  : _paths{retrieveSystemPaths(filename)}
{}
