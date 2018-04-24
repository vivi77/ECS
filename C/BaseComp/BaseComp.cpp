#include "BaseComp.hh"

namespace lel::ecs::component
{
  BaseComp::BaseComp(const entity::IDEntity& id)
    : _entityOwnerID{id}
  {}

  entity::IDEntity BaseComp::getEntityOwnerID() const
  {
    return _entityOwnerID.value();
  }

  void BaseComp::setEntityOwner(const entity::IDEntity& id)
  {
    _entityOwnerID = id;
  }
} /* !lel::ecs::component */
