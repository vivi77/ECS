#pragma once

#include "emanager_export.h"
#include "IEListener.hh"
#include "log/Log.hh"
#include <vector>
#include <unordered_map>

class IS;

class EMANAGER_EXPORT EManager
{
public:
  using EventID = unsigned; //EIDGenerator::ID;
  using Dtor = void(*)(void*);
  using IEListenerPtr = std::shared_ptr<IEListener>;
  using SPtr = std::shared_ptr<IS>;

public:
  template <typename Event, typename ... Args>
  static void fire(Args&& ... args)
  {
    auto it = _registeredEvents.find(Event::getEventID());
    if (it == std::end(_registeredEvents))
    {
      lel::Log{} << "Event dtor (ID:" << Event::getEventID() << ") not found\n"
        << "Don't forget to register your event destructor with "
        << "'registerEventDtor' method";
      return ;
    }

    auto ev = std::shared_ptr<Event>(new Event(args...), it->second);
    for (auto& it : _listeners)
      it->update(ev);
  }

  static void registerListener(const IEListenerPtr& listener);
  static void deregisterListener(const IEListenerPtr& listener);
  static void registerListenerSystem(const SPtr& s);
  static void deregisterListenerSystem(const SPtr& s);
  static void registerEventDtor(const EventID id, Dtor dtor);

private:
  static std::vector<IEListenerPtr> _listeners;
  static std::unordered_map<EventID, Dtor> _registeredEvents;
};
