#include "EIDGenerator.hh"

namespace lel
{
  namespace ecs
  {
    namespace event
    {
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
    } /* !event */
  } /* !ecs */
} /* !lel */
