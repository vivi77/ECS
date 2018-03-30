#include "CManager.hh"

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      std::unordered_map<CManager::CID, CManager::Dtor> CManager::_registerComponentDtor;
      std::vector<component::CManager::CPtr> component::CManager::_components;

      void component::CManager::registerCompDtor(const CID id, Dtor dtor)
      {
        auto it = _registerComponentDtor.find(id);
        auto ev = event::CManagerEvent::Type::COMP_ALREADY_ADDED;
        if (it == std::end(_registerComponentDtor))
        {
          _registerComponentDtor.emplace(std::make_pair(id, dtor));
          ev = event::CManagerEvent::Type::COMP_ADDED;
        }
        lel::ecs::event::EManager::fire<event::CManagerEvent>(ev, id);
      }
    } /* !event */
  } /* !ecs */
} /* !lel */
