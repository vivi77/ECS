#pragma once

#include "C/CManager/cmanager_export.h"
#include "E/EManager/EManager.hh"
#include "E/CManagerEvent/CManagerEvent.hh"
#include "Utility/Fwd.hh"
#include <vector>

namespace lel::ecs::component
{
  class CMANAGER_EXPORT CManager
  {
  public:
    using CPtr = std::shared_ptr<IC>;

  public:
    template <class C, typename ... Args>
    static std::unique_ptr<C> createComp(Args&& ... args)
    {
      auto comp = std::make_shared<C>(std::forward<Args>(args)...);
      event::EManager::fire<event::CManagerEvent>(
        event::CManagerEvent::Type::COMP_CREATED, C::getComponentID());
      _components.emplace_back(comp);
      return comp;
    }

  private:
    static std::vector<CPtr> _components;
  };
} /* !lel::ecs::component */
