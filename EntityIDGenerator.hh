#pragma once

#include "Utility/IIDGenerator.hpp"
#include "Utility/Fwd.hh"
#include "IDEntity.hh"

namespace lel::ecs::entity
{
  class EntityIDGenerator : public utility::IIDGenerator<IDEntity>
  {
  public:
    using ID = IDEntity;

  public:
    ID generateID() override;

  private:
    ID _id{0};
  };
} /* !lel::ecs::entity */
