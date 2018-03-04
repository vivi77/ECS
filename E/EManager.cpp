#include "EManager.hh"
#include "log/Log.hh"
#include "IS.hh"
#include <algorithm>

std::vector<EManager::IEListenerPtr> EManager::_listeners;

void EManager::fire(const IEListener::EPtr& e)
{
  lel::Log{} << "Fire event: ID: " << e->getID() << "\n";
  for (auto& it : _listeners)
    it->update(e);
}

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

EManager::IEListenerPtr EManager::castSystemToListener(const EManager::SPtr& s)
{
  // No better solution yet
  return std::dynamic_pointer_cast<IEListener>(s);
}
