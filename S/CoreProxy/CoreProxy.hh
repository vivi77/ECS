#pragma once

#include "S/CoreProxy/coreproxy_export.h"
#include "E/EManager/EManager.hh"
#include "Entity/EntityManager.hh"
#include "CoreSystemData.hh"
#include <list>
#include <iostream>

namespace lel::ecs
{
  // This class serve as a proxy to the class Core
  //   It provides services that Core should provide. But it does not need to the
  //   users of theses services to include/link against Core (which is not in a
  //   shared library)
  class COREPROXY_EXPORT CoreProxy
  {
  public:
    using SystemContainer = std::list<CoreSystemData>; //Core::'Container of the systems'

  public:
    CoreProxy(SystemContainer&, entity::EntityManager&, event::EManager&);
    entity::EntityManager::EntityPtr createEntity(std::initializer_list<entity::EntityManager::ComponentPtr>);
    void destroyEntity(const entity::EntityManager::ID id);

    template <class Event, typename ... Args>
    void fire(Args&& ... args)
    {
      _eventManager.fire<Event>(std::forward<Args>(args)...);
    }

  private:
    SystemContainer& _systems;
    entity::EntityManager& _entityManager;
    event::EManager& _eventManager;
  };
} /* !lel::ecs */
