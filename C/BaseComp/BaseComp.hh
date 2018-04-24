#pragma once

#include "C/IC.hh"
#include "Entity/IDEntity.hh"
#include <optional>

namespace lel::ecs::component
{
  class BaseComp : public IC
  {
  public:
    BaseComp() = default;
    BaseComp(const entity::IDEntity&);
    ~BaseComp() override = default;

    entity::IDEntity getEntityOwnerID() const;

    void setEntityOwner(const entity::IDEntity&);

  private:
    std::optional<entity::IDEntity> _entityOwnerID;
  };
} /* !lel::ecs::component */
