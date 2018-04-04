#include "CIDGenerator.hh"
#include <memory>

template <>
std::unique_ptr<lel::ecs::utility::IIDGenerator<lel::ecs::component::IDComponent>> createGenerator()
{
  return std::make_unique<lel::ecs::component::CIDGenerator>();
}

namespace lel::ecs::component
{
  CIDGenerator::ID CIDGenerator::generateID()
  {
    return _id++;
  }

  namespace old
  {
    CIDGenerator::CIDGenerator()
      : _idGenerator{0}
    {
      ;
    }

    CIDGenerator::ID CIDGenerator::generateID()
    {
      return _idGenerator++;
    }

    CIDGenerator& CIDGenerator::getSingleton()
    {
      static CIDGenerator singleton;
      return singleton;
    }
  } /* !old */
} /* !lel::ecs::component */
