#pragma once

#include "E/EManager/emanager_export.h"
#include "E/IEListener.hh"
#include <vector>

namespace lel::ecs
{
  namespace event
  {
    class EMANAGER_EXPORT EManager
    {
    public:
      using Dtor = void(*)(void*);
      using IEListenerPtr = std::shared_ptr<IEListener>;

    public:
      template <typename Event, typename ... Args>
      static void fire(Args&& ... args)
      {
        auto ev = std::shared_ptr<Event>(new Event(std::forward<Args>(args)...));
        for (auto& it : _listeners)
          it->update(ev);
      }

      static void registerListener(const IEListenerPtr& listener);
      static void deregisterListener(const IEListenerPtr& listener);

    private:
      static std::vector<IEListenerPtr> _listeners;
    };
  } /* !event */
} /* !lel::ecs */
