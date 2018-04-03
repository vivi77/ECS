#include "SIDGenerator.hh"

namespace lel::ecs::system
{
  SIDGenerator::SIDGenerator()
    : _idGenerator{0}
  {
    ;
  }

  SIDGenerator::ID SIDGenerator::generateID()
  {
    return _idGenerator++;
  }

  SIDGenerator& SIDGenerator::getSingleton()
  {
    static SIDGenerator singleton;
    return singleton;
  }
} /* !lel::ecs::system */
