#pragma once

#include "OSDLLoader/OSDLLoader.hh"
#include "S/IS.hh"
#include <experimental/filesystem>

namespace lel::ecs
{
  struct CoreSystemData
  {
    std::experimental::filesystem::path path;
    lel::OSDLLoader loader;
    std::shared_ptr<lel::ecs::system::IS> sys;
  };
} /* !lel::ecs */
