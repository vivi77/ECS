#pragma once

#include "OSDLLoader/OSDLLoader.hh"
#include "S/IS.hh"
#include <experimental/filesystem>

struct CoreSystemData
{
  std::experimental::filesystem::path path;
  lel::OSDLLoader loader;
  std::shared_ptr<IS> sys;
};
