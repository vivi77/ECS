#include "EManager.hh"
#include "EManagerEvent.hh"
#include "IS.hh"
#include <algorithm>
#include <sstream>

namespace
{
  std::string to_string(void *ptr)
  {
    std::stringstream ss;
    ss << ptr;
    return ss.str();
  }

  // No better solution yet
  EManager::IEListenerPtr castSystemToListener(const EManager::SPtr& s)
  {
    auto l = std::dynamic_pointer_cast<IEListener>(s);

    if (!l)
      EManager::fire<EManagerEvent>(EManagerEvent::Type::NOT_LISTENER, s->getID());
    return l;
  }
} /* ! */

std::vector<EManager::IEListenerPtr> EManager::_listeners;
std::unordered_map<EManager::EventID, EManager::Dtor> EManager::_registeredEvents;

void EManager::registerListener(const IEListenerPtr& listener)
{
  auto ev = EManagerEvent::Type::LISTENER_ALREADY_ADDED;

  auto beginIt = std::begin(_listeners);
  auto endIt = std::end(_listeners);
  auto it = std::find(beginIt, endIt, listener);
  if (it == endIt)
  {
    _listeners.emplace_back(listener);
    ev = EManagerEvent::Type::LISTENER_ADDED;
  }
  EManager::fire<EManagerEvent>(ev, to_string(listener.get()));
}

void EManager::deregisterListener(const IEListenerPtr& listener)
{
  auto ev = EManagerEvent::Type::LISTENER_NOT_FOUND;

  auto beginIt = std::begin(_listeners);
  auto endIt = std::end(_listeners);
  auto it = std::find(beginIt, endIt, listener);
  if (it != endIt)
  {
    _listeners.erase(it);
    ev = EManagerEvent::Type::LISTENER_REMOVED;
  }
  EManager::fire<EManagerEvent>(ev, to_string(listener.get()));
}

void EManager::registerListenerSystem(const EManager::SPtr& s)
{
  auto listener = castSystemToListener(s);
  if (listener)
    registerListener(listener);
}

void EManager::deregisterListenerSystem(const EManager::SPtr& s)
{
  auto listener = castSystemToListener(s);
  if (listener)
    deregisterListener(listener);
}

void EManager::registerEventDtor(const EventID id, Dtor dtor)
{
  auto ev = EManagerEvent::Type::EVENT_ALREADY_ADDED;

  auto it = _registeredEvents.find(id);
  if (it == std::end(_registeredEvents))
  {
    _registeredEvents.insert(std::make_pair(id, dtor));
    ev = EManagerEvent::Type::EVENT_ADDED;
  }
  EManager::fire<EManagerEvent>(ev, id);
}
