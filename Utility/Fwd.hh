#pragma once

#include <memory>

namespace lel::ecs
{
  class Core;
  class CoreProxy;
  class StartupLoader;

  namespace system
  {
    //using IDSystem = unsigned int;
    class IDSystem;
    class IS;
    class SIDGenerator;
  } /* !system */

  namespace component
  {
    class IDComponent;
    class IC;
    class CIDGenerator;
  } /* !component */

  namespace event
  {
    class IDEvent;
    class IE;
    class EIDGenerator;
    class IEListener;
  } /* !event */

  namespace entity
  {
    class IDEntity;
    class Entity;
    class EntityIDGenerator;
    class EntityManager;
  } /* !entity */

  namespace utility
  {
    template <typename ID>
    class IIDGenerator;
  }
} /* !lel::ecs */

template <typename ID>
std::unique_ptr<lel::ecs::utility::IIDGenerator<ID>> createGenerator();
