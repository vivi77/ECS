#include "EManager.hh"
#include "E/EManagerEvent/EManagerEvent.hh"
#include "S/IS.hh"
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
  lel::ecs::event::EManager::IEListenerPtr castSystemToListener(const lel::ecs::event::EManager::SPtr& s)
  {
    auto l = std::dynamic_pointer_cast<lel::ecs::event::IEListener>(s);

    if (!l)
      lel::ecs::event::EManager::fire<lel::ecs::event::EManagerEvent>(lel::ecs::event::EManagerEvent::Type::NOT_LISTENER, s->getID());
    return l;
  }
} /* ! */

namespace lel::ecs::event
{
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
      _registeredEvents.emplace(std::make_pair(id, dtor));
      ev = EManagerEvent::Type::EVENT_ADDED;
    }
    EManager::fire<EManagerEvent>(ev, id);
  }

  void EManager::eventNotFound(const EventID id)
  {
    EManager::template fire<EManagerEvent>(EManagerEvent::Type::EVENT_DTOR_NOT_FOUND, id);
  }
} /* !lel::ecs::event */
