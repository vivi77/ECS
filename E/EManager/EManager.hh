#pragma once

#include "E/EManager/emanager_export.h"
#include "E/IEListener.hh"
#include <vector>
#include <unordered_map>

namespace lel::ecs
{
  namespace system
  {
    class IS;
  } /* !system */

  namespace event
  {
    class EMANAGER_EXPORT EManager
    {
    public:
      using EventID = unsigned; //EIDGenerator::ID;
      using Dtor = void(*)(void*);
      using IEListenerPtr = std::shared_ptr<IEListener>;
      using SPtr = std::shared_ptr<system::IS>;

    public:
      template <typename Event, typename ... Args>
      static void fire(Args&& ... args)
      {
        //auto it = _registeredEvents.find(Event::getEventID());
        //if (it == std::end(_registeredEvents))
        //{
          //eventNotFound(Event::getEventID());
          //return ;
        //}

        auto ev = std::shared_ptr<Event>(new Event(std::forward<Args>(args)...));
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

    private:
      static void eventNotFound(const EventID id);
    };
  } /* !event */
} /* !lel::ecs */
