#pragma once

#include "cmanager_export.h"
#include "IC.hh"
#include "EManager.hh"
#include "CManagerEvent.hh"
#include <memory>
#include <unordered_map>

class CMANAGER_EXPORT CManager
{
public:
  using CPtr = std::shared_ptr<IC>;
  using CID = unsigned; //CIDGenerator::ID
  using Dtor = void(*)(IC*);

public:
  template <class C, typename ... Args>
  static std::unique_ptr<C> createComp(Args&& ... args)
  {
    auto it = _registerComponentDtor.find(C::getCompID());
    if (it == std::end(_registerComponentDtor))
    {
      EManager::fire<CManagerEvent>(CManagerEvent::Type::COMP_DTOR_NOT_FOUND, C::getCompID());
      return nullptr;
    }

    std::unique_ptr<C> comp{new C{std::forward<Args>(args)...,}, it->second};
    EManager::fire<CManagerEvent>(CManagerEvent::Type::COMP_CREATED, comp->getId());
    return comp;
  }

  static void registerCompDtor(const CID, Dtor);

private:
  static std::unordered_map<CID, Dtor> _registerComponentDtor;
};
