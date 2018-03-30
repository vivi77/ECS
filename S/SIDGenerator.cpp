#include "SIDGenerator.hh"

namespace lel
{
  namespace ecs
  {
    namespace system
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
    }
  }
}
