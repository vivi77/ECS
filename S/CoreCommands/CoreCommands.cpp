#include "CoreCommands.hh"

namespace lel::ecs::system
{
  CoreCommands::CoreCommands(CoreProxy& proxy)
    : CRTPS{proxy}
  {}

  void CoreCommands::exec()
  {}

  void CoreCommands::registerEntity(const EntityPtr&)
  {}

  void CoreCommands::deregisterEntity(const EntityPtr&)
  {}

  void CoreCommands::setup()
  {}

  void CoreCommands::atRemove()
  {}

  void CoreCommands::update(const EPtr&)
  {}
} /* !lel::ecs::system */
