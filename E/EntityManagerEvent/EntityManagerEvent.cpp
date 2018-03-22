#include "EntityManagerEvent.hh"

EntityManagerEvent::EntityManagerEvent(const Type t)
  : _t{t}
{}

EntityManagerEvent::EntityManagerEvent(const Type t, const EntityID id)
  : _t{t}
  , _id{id}
{}

EntityManagerEvent::Type EntityManagerEvent::getType() const
{
  return _t;
}

EntityManagerEvent::EntityID EntityManagerEvent::getEntityID() const
{
  return _id;
}
