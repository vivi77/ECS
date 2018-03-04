#include "SIDGenerator.hh"

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
