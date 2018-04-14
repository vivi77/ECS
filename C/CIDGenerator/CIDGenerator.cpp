#include "CIDGenerator.hh"
#include "Utility/Fwd.hh"

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
} /* !lel::ecs::component */
