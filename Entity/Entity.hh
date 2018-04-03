#pragma once

#include "C/IC.hh"
#include "Entity/entitylogic_export.h"
#include <vector>
#include <memory>

namespace lel::ecs::entity
{
  class ENTITYLOGIC_EXPORT Entity
  {
  public:
    using CPtr = std::shared_ptr<lel::ecs::component::IC>;
    using CContainer = std::vector<CPtr>;

  public:
    using ID = unsigned;

  public:
    Entity(const ID, std::initializer_list<CPtr>);

    ID getID() const;
    CContainer getComponents() const;

    void addComponent(const CPtr& comp);
    void removeComponent(const lel::ecs::component::IC::ID);

  private:
    ID _id;
    CContainer _components;
  };
} /* !lel::ecs::entity */
