#pragma once

#include "dlloader/OSDLLoader.hpp"
#include "S/IS.hh"
#include <experimental/filesystem>

struct CoreSystemData
{
  std::experimental::filesystem::path path;
  lel::OSDLLoader loader;
  std::shared_ptr<IS> sys;
};
