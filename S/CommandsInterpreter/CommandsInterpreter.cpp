#include "CommandsInterpreter.hh"
#include "E/TextInputUpdaterEvents/TextInputUpdaterEventsOut.hpp"

namespace lel::ecs::system
{
  CommandsInterpreter::CommandsInterpreter(CoreProxy& proxy)
    : CRTPS{proxy}
  {}

  void CommandsInterpreter::exec()
  {}

  void CommandsInterpreter::registerEntity(const EntityPtr& entity)
  {
    Wrapper item;
    auto comps = entity->getComponents();
    for (const auto& comp : comps)
    {
      if (comp->getID() == component::CommandsStr::getComponentID())
        item.commands = std::static_pointer_cast<component::CommandsStr>(comp);
    }

    if (item.isValid())
      _entities.emplace_back(item);
  }

  void CommandsInterpreter::deregisterEntity(const EntityPtr& entity)
  {
    const auto end = std::end(_entities);
    const auto pred = [&entity](auto& it)
    {
      return it.commands->getEntityOwnerID() == entity->getID();
    };
    const auto it = std::find_if(std::begin(_entities), end, pred);
    if (it != end)
      _entities.erase(it);
  }

  void CommandsInterpreter::setup()
  {}

  void CommandsInterpreter::atRemove()
  {}

  void CommandsInterpreter::update(const EPtr& e)
  {
    if (e->getID() == event::TextInputUpdaterEventsOut<std::string>::getEventID())
    {
      auto event = std::static_pointer_cast<event::TextInputUpdaterEventsOut<std::string>>(e);
      for (const auto& ent : _entities)
      {
        if (event->getSenderID() == ent.commands->_commandsOwnerId)
        {
          switch (event->getType())
          {
            case event::TextInputUpdaterEventsOut<std::string>::Type::INPUT_SEND:
              {
                const auto key = event->getInput();
                const auto it = ent.commands->_functions.find(key);
                if (it != std::end(ent.commands->_functions))
                  it->second();
              }
              break;
          }
        }
      }
    }
  }
} /* !lel::ecs::component */
