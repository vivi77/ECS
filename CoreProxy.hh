#pragma once

#include "CoreSystemData.hh"
#include "EManager.hh"
#include "EntityManager.hh"
#include <list>

namespace lel::ecs
{
  // This class serve as a proxy to the class Core
  //   It provides services that Core should provide. But it does not need to the
  //   users of theses services to include/link against Core (which is not in a
  //   shared library)
  //
  // MUST NOT CONTAIN A Core class inside. Else this class does not do its work
  // which is uncoupling the Core class and all systems
  class CoreProxy
  {
  public:
    using SystemContainer = std::list<CoreSystemData>; //Core::'Container of the systems'

  public:
    CoreProxy(SystemContainer&, entity::EntityManager&, event::EManager&, bool&);

    entity::EntityManager::EntityPtr createEntity(std::initializer_list<entity::EntityManager::ComponentPtr>);
    void destroyEntity(const entity::EntityManager::ID id);
    void stopCore();
    void addSystem(const std::string&);
    void removeSystem(const std::string&);
    void reloadSystem(const std::string&);

    template <class Event, typename ... Args>
    void fire(Args&& ... args)
    {
      _eventManager.fire<Event>(std::forward<Args>(args)...);
    }

  private:
    SystemContainer& _systems;
    entity::EntityManager& _entityManager;
    event::EManager& _eventManager;
    bool& _quit;

    std::vector<std::string> _systemsToAdd;
    std::vector<std::string> _systemsToRemove;
    std::vector<std::string> _systemsToReload;

    // Authorized as it should be an extension of Core for system usage
    friend Core;
  };
} /* !lel::ecs */
