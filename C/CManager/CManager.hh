#pragma once

#include "C/CManager/cmanager_export.h"
#include "C/IC.hh"
#include "S/IS.hh"
#include "E/EManager.hh"
#include "E/CManagerEvent/CManagerEvent.hh"
#include <memory>
#include <unordered_map>

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      class CMANAGER_EXPORT CManager
      {
      public:
        using CPtr = std::shared_ptr<component::IC>;
        using CID = unsigned; //CIDGenerator::ID
        using Dtor = void(*)(component::IC*);
        using SPtr = std::shared_ptr<system::IS>;

      public:
        template <class C, typename ... Args>
        static std::unique_ptr<C> createComp(Args&& ... args)
        {
          auto it = _registerComponentDtor.find(C::getCompID());
          if (it == std::end(_registerComponentDtor))
          {
            event::EManager::fire<event::CManagerEvent>(event::CManagerEvent::Type::COMP_DTOR_NOT_FOUND, C::getCompID());
            return nullptr;
          }

          std::shared_ptr<C> comp{new C{std::forward<Args>(args)...,}, it->second};
          event::EManager::fire<event::CManagerEvent>(event::CManagerEvent::Type::COMP_CREATED, comp->getId());
          _components.emplace_back(comp);
          return comp;
        }

        static void registerCompDtor(const CID, Dtor);

      private:
        static std::unordered_map<CID, Dtor> _registerComponentDtor;
        static std::vector<CPtr> _components;
      };
    } /* !compeonent */
  } /* !ecs */
} /* !lel */
