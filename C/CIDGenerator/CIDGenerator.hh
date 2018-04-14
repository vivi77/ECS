#pragma once

#include "C/IDComponent.hh"
#include "C/CIDGenerator/cidgen_export.h"
#include "Utility/IIDGenerator.hpp"

namespace lel::ecs::component
{
  class CIDGEN_EXPORT CIDGenerator : public utility::IIDGenerator<IDComponent>
  {
  public:
    using ID = IDComponent;

  public:
    ID generateID() override;

  private:
    ID _id{0};
  };
} /* !lel::ecs::component */
