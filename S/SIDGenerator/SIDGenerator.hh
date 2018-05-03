#pragma once

#include "S/SIDGenerator/sidgen_export.h"
#include "S/IDSystem.hh"
#include "Utility/IIDGenerator.hpp"

namespace lel::ecs::system
{
  class SIDGEN_EXPORT SIDGenerator : public utility::IIDGenerator<IDSystem>
  {
  public:
    IDSystem generateID();

  private:
    IDSystem _id{0};
  };
} /* !lel::ecs::system */
