#include "CIDGenerator.hh"

namespace lel::ecs::component
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
} /* !lel::ecs::component */
