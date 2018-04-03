#pragma once

#include "S/IS.hh"
#include "CoreSystemData.hh"
#include <list>

namespace lel::ecs
{
  class Core;

  // This class serve as a proxy to the class Core
  //   It provides services that Core should provide. But it does not need to the
  //   users of theses services to include Core (which is not in a shared library)
  class CoreSystemProxy
  {
  public:
    using SystemContainer = std::list<CoreSystemData>; //Core::'Container of the systems'

  public:
    static void registerEntityInSystems(const std::shared_ptr<Entity>& entity);

  private:
    static void setSystemsList(SystemContainer& systems);

  private:
    static SystemContainer* _systems;

    friend Core;
  };
} /* !lel::ecs */

// setSystemsList is private to avoid other classes to misuse this class.
//  Only Core class should be able to access it
