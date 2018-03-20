#include "EntityIDGenerator.hh"

EntityIDGenerator::ID EntityIDGenerator::_id = 0;

EntityIDGenerator::ID EntityIDGenerator::generateID()
{
  return _id++;
}
