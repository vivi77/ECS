#include "CIDGenerator.hh"

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      CIDGenerator::CIDGenerator()
        : _idGenerator{0}
      {
        ;
      }

      CIDGenerator::ID CIDGenerator::generateID()
      {
        return _idGenerator++;
      }

      CIDGenerator& CIDGenerator::getSingleton()
      {
        static CIDGenerator singleton;
        return singleton;
      }
    }
  }
}

