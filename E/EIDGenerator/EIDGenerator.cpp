#include "EIDGenerator.hh"

template <>
std::unique_ptr<lel::ecs::utility::IIDGenerator<lel::ecs::event::IDEvent>> EIDGEN_EXPORT createGenerator()
{
  return std::make_unique<lel::ecs::event::EIDGenerator>();
}

namespace lel::ecs::event
{
  EIDGenerator::ID EIDGenerator::generateID()
  {
    return _id++;
  }
} /* !lel::ecs::event */
