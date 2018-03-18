#include "EManager.hh"
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
    _listeners.emplace_back(listener);
}

void EManager::deregisterListener(const IEListenerPtr& listener)
{
  auto beginIt = std::begin(_listeners);
  auto endIt = std::end(_listeners);
  auto it = std::find(beginIt, endIt, listener);
  if (it != endIt)
    _listeners.erase(it);
}

void EManager::registerListenerSystem(const EManager::SPtr& s)
{
  auto listener = castSystemToListener(s);
  if (listener == nullptr)
    return ;

  auto beginIt = std::begin(_listeners);
  auto endIt = std::end(_listeners);
  auto it = std::find(beginIt, endIt, listener);
  if (it == endIt)
    _listeners.emplace_back(listener);
}

void EManager::deregisterListenerSystem(const EManager::SPtr& s)
{
  auto listener = castSystemToListener(s);
  if (listener == nullptr)
    return ;

  auto beginIt = std::begin(_listeners);
  auto endIt = std::end(_listeners);
  auto it = std::find(beginIt, endIt, listener);
  if (it != endIt)
    _listeners.erase(it);
}

void EManager::registerEventDtor(const EventID id, Dtor dtor)
{
  auto it = _registeredEvents.find(id);
  if (it == std::end(_registeredEvents))
    _registeredEvents.insert(std::make_pair(id, dtor));
}
