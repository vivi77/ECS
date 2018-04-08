#pragma once

#include "C/CIDGenerator/cidgen_export.h"
#include "Utility/IIDGenerator.hpp"
#include "Utility/Fwd.hh"

namespace lel::ecs::component
{
  class CIDGEN_EXPORT CIDGenerator : public utility::IIDGenerator<IDComponent>
  {
  public:
    using ID = IDComponent;

  public:
    ID generateID() override;

  private:
    ID _id;
  };
} /* !lel::ecs::component */
