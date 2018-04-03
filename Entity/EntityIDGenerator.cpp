#include "EntityIDGenerator.hh"

namespace lel::ecs::entity
{
  EntityIDGenerator::ID EntityIDGenerator::_id = 0;

  EntityIDGenerator::ID EntityIDGenerator::generateID()
  {
    return _id++;
  }
} /* !lel::ecs::entity */
