#include "CManager.hh"

void CManager::registerCompDtor(const CID id, Dtor dtor)
{
  auto it = _registerComponentDtor.find(id);
  auto ev = CManagerEvent::Type::COMP_ALREADY_ADDED;
  if (it == std::end(_registerComponentDtor))
  {
    _registerComponentDtor.emplace(std::make_pair(id, dtor));
    ev = CManagerEvent::Type::COMP_ADDED;
  }
  EManager::fire<CManagerEvent>(ev, id);
}
