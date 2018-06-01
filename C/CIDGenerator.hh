#pragma once

#include "IDComponent.hh"
#include "Utility/IIDGenerator.hpp"

namespace lel::ecs::component
{
  class CIDGenerator : public utility::IIDGenerator<IDComponent>
  {
  public:
    using ID = IDComponent;

  public:
    ID generateID() override;

  private:
    ID _id{0};
  };
} /* !lel::ecs::component */
