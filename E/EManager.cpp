#include "EManager.hh"
#include "EManagerEvent.hh"
#include "IS.hh"
#include <algorithm>

namespace
{
  EManager::IEListenerPtr castSystemToListener(const EManager::SPtr& s)
  {
    // No better solution yet
    return std::dynamic_pointer_cast<IEListener>(s);
  }
} /* ! */

std::vector<EManager::IEListenerPtr> EManager::_listeners;
std::unordered_map<EManager::EventID, EManager::Dtor> EManager::_registeredEvents;

void EManager::registerListener(const IEListenerPtr& listener)
{
  auto beginIt = std::begin(_listeners);
  auto endIt = std::end(_listeners);
  auto it = std::find(beginIt, endIt, listener);
  if (it == endIt)
  {
    _listeners.emplace_back(listener);
    EManager::fire<EManagerEvent>(EManagerEvent::Type::LISTENER_ADDED);
  }
}

void EManager::deregisterListener(const IEListenerPtr& listener)
{
  auto beginIt = std::begin(_listeners);
  auto endIt = std::end(_listeners);
  auto it = std::find(beginIt, endIt, listener);
  if (it != endIt)
  {
    _listeners.erase(it);
    EManager::fire<EManagerEvent>(EManagerEvent::Type::LISTENER_REMOVED);
  }
}

void EManager::registerListenerSystem(const EManager::SPtr& s)
{
  auto listener = castSystemToListener(s);
  if (listener == nullptr)
  {
    EManager::fire<EManagerEvent>(EManagerEvent::Type::NOT_LISTENER, s->getID());
    return ;
  }
  registerListener(listener);
}

void EManager::deregisterListenerSystem(const EManager::SPtr& s)
{
  auto listener = castSystemToListener(s);
  if (listener == nullptr)
  {
    EManager::fire<EManagerEvent>(EManagerEvent::Type::NOT_LISTENER, s->getID());
    return ;
  }
  deregisterListener(listener);
}

void EManager::registerEventDtor(const EventID id, Dtor dtor)
{
  auto it = _registeredEvents.find(id);
  if (it == std::end(_registeredEvents))
  {
    _registeredEvents.insert(std::make_pair(id, dtor));
    EManager::fire<EManagerEvent>(EManagerEvent::Type::EVENT_ADDED, id);
  }
}
