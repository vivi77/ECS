#pragma once

#include "IEListener.hh"
#include <vector>

namespace lel::ecs::event
{
  class EManager
  {
  public:
    using Dtor = void(*)(void*);
    using IEListenerPtr = std::shared_ptr<IEListener>;

  public:
    template <typename Event, typename ... Args>
    void fire(Args&& ... args)
    {
      auto ev = std::shared_ptr<Event>(new Event(std::forward<Args>(args)...));
      for (auto& it : _listeners)
        it->update(ev);
    }

    void registerListener(const IEListenerPtr& listener);
    void deregisterListener(const IEListenerPtr& listener);

  private:
    std::vector<IEListenerPtr> _listeners;
  };
} /* !lel::ecs */
