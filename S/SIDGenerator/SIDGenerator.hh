#pragma once

#include "S/sidgen_export.h"
#include "Utility/IIDGenerator.hpp"
#include "Utility/Fwd.hh"

namespace lel::ecs::system
{
  class SIDGEN_EXPORT SIDGenerator : public utility::IIDGenerator<IDSystem>
  {
  public:
    IDSystem generateID();

  private:
    IDSystem _id;
  };
} /* !lel::ecs::system */
