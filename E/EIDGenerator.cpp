#include "EIDGenerator.hh"

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
