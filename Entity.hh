#pragma once

#include "IDEntity.hh"
#include "IDComponent.hh"
#include "Utility/Fwd.hh"
#include <vector>

namespace lel::ecs::entity
{
  class Entity
  {
  public:
    using CPtr = std::shared_ptr<component::IC>;
    using CContainer = std::vector<CPtr>;

  public:
    using ID = IDEntity;

  public:
    Entity(const ID, std::initializer_list<CPtr>);

    ID getID() const;
    CContainer getComponents() const;

    void addComponent(const CPtr& comp);
    void removeComponent(const component::IDComponent&);

  private:
    ID _id;
    CContainer _components;
  };
} /* !lel::ecs::entity */
