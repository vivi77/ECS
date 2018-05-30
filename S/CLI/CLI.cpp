#include "CLI.hh"
#include "E/CLISystemEvent/CLISystemEvent.hh"
#include "E/CoreCommandsEvent/CoreCommandsEvent.hh"

ECS_CREATE_IDSYSTEM(CLI)

namespace lel::ecs::system
{
  CLI::CLI(CoreProxy& proxy)
    : CRTPS{proxy}
    , _cliparser{}
    , _enabled{true}
  {}

  void CLI::exec()
  {
    if (!_enabled)
      return ;

    std::cout << "$> ";
    std::string input;
    std::getline(std::cin, input);

    if (std::cin.eof())
    {
      getProxy().fire<event::CoreCommandsEvent>();
      std::cin.clear();
    }
    else if (std::cin.good())
    {
      input += '\n';
      getProxy().fire<event::CoreCommandsEvent>(input);
    }
  }

  void CLI::registerEntity(const EntityPtr&)
  {}

  void CLI::deregisterEntity(const EntityPtr&)
  {}

  void CLI::setup()
  {}

  void CLI::atRemove()
  {}

  void CLI::update(const EPtr& ptr)
  {
    if (ptr->getID() == event::CLISystemEvent::getEventID())
    {
      auto ev = std::static_pointer_cast<event::CLISystemEvent>(ptr);
      switch (ev->getType())
      {
        case event::CLISystemEvent::Type::DISABLE:
          _enabled = false;
          break;
        case event::CLISystemEvent::Type::ENABLE:
          _enabled = true;
          break;
        default: break;
      }
    }
  }
} /* !lel::ecs::system */
