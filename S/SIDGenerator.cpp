#include "SIDGenerator.hh"

template <>
std::unique_ptr<lel::ecs::utility::IIDGenerator<lel::ecs::system::IDSystem>> createGenerator()
{
  return std::make_unique<lel::ecs::system::SIDGenerator>();
}

namespace lel::ecs::system
{
  IDSystem SIDGenerator::generateID()
  {
    return _id++;
  }

  namespace old
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
  } /* !old */
} /* !lel::ecs::system */
