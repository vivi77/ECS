#pragma once

#include "dlloader/OSLoader.hpp"
#include "S/IS.hh"
#include <experimental/filesystem>

struct CoreSystemData
{
  std::experimental::filesystem::path path;
  lel::OSLoader loader;
  std::shared_ptr<IS> sys;
};
