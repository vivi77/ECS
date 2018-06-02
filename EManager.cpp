#include "EManager.hh"
#include "EManagerEvent.hh"
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
} /* ! */

namespace lel::ecs::event
{
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
} /* !lel::ecs::event */
