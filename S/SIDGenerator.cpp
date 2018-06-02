#include "SIDGenerator.hh"
#include "Utility/Fwd.hh"

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
} /* !lel::ecs::system */
