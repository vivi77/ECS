#include "EIDGenerator.hh"

namespace lel::ecs::event
{
  EIDGenerator::EIDGenerator()
    : _idGenerator{0}
  {
    ;
  }

  EIDGenerator::ID EIDGenerator::generateID()
  {
    return _idGenerator++;
  }

  EIDGenerator& EIDGenerator::getSingleton()
  {
    static EIDGenerator singleton;
    return singleton;
  }
} /* !lel::ecs::event */
