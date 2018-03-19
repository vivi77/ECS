#pragma once

#include "cmanager_export.h"
#include "IC.hh"
#include "IS.hh"
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
  using SPtr = std::shared_ptr<IS>;

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

    std::shared_ptr<C> comp{new C{std::forward<Args>(args)...,}, it->second};
    EManager::fire<CManagerEvent>(CManagerEvent::Type::COMP_CREATED, comp->getId());
    _components.emplace_back(comp);
    return comp;
  }

  static void registerCompDtor(const CID, Dtor);

private:
  static std::unordered_map<CID, Dtor> _registerComponentDtor;
  static std::vector<CPtr> _components;
};
