#include "TextInputUpdater.hh"
#include "E/IE.hh"
#include "E/IDEvent.hh"
#include "E/CoreCommandsEvent/CoreCommandsEvent.hh"

ECS_CREATE_IDSYSTEM(TextInputUpdater)

namespace
{
  bool isTextInputValidForUpdate(const lel::ecs::component::TextInputState& obj)
  {
    return obj.active && obj.focused;
  }
} /* ! */

namespace lel::ecs::system
{
  TextInputUpdater::TextInputUpdater(CoreProxy& proxy)
    : CRTPS{proxy}
  {
  }

  void TextInputUpdater::exec()
  {
  }

  void TextInputUpdater::registerEntity(const EntityPtr& entity)
  {
    using TIS = component::TextInputStr;
    using TT = component::TerminalText;
    using TIState = component::TextInputState;

    Item item;
    auto comps = entity->getComponents();
    for (auto& comp : comps)
    {
      const auto compID = comp->getID();
      if (compID == TIS::getComponentID())
        item.inputComp = std::static_pointer_cast<TIS>(comp);
      else if (compID == TT::getComponentID())
        item.textComp = std::static_pointer_cast<TT>(comp);
      else if (compID == TIState::getComponentID())
        item.inputStateComp = std::static_pointer_cast<TIState>(comp);
    }
    if (item.isValid())
      _components.emplace_back(item);
  }

  void TextInputUpdater::deregisterEntity(const EntityPtr& entity)
  {
    const auto end = std::end(_components);
    const auto pred = [&entity](const auto& it)
    {
      return it.inputComp->getEntityOwnerID() == entity->getID();
    };
    const auto it = std::find_if(std::begin(_components),
                                 std::end(_components), pred);
    if (it != end)
      _components.erase(it);
  }

  void TextInputUpdater::setup()
  {
  }

  void TextInputUpdater::atRemove()
  {
  }

  void TextInputUpdater::update(const EPtr& ptr)
  {
    using TIEventIn = event::TextInputUpdaterEventsIn<std::string>;

    if (ptr->getID() == TIEventIn::getEventID())
    {
      const auto ev = std::static_pointer_cast<TIEventIn>(ptr);
      basicUpdate(ev);
    }
  }

  // It is advised to create its own event if you plan to make this system send
  // out new events
  void TextInputUpdater::basicUpdate(const std::shared_ptr<DefaultInputEvent>& ev)
  {
    const bool isBroadcast = ev->getReceiverID().empty();
    switch (ev->getType())
    {
      case DefaultInputEvent::Type::ADD_CHAR:
        std::for_each(std::begin(_components), std::end(_components),
          [&ev, this, isBroadcast](auto& item) -> void
          {
            if (!::isTextInputValidForUpdate(*item.inputStateComp))
              return ;

            const auto itemID = item.inputComp->textInputID;
            if (isBroadcast || itemID == ev->getReceiverID())
            {
              const auto c = ev->getChar();
              if (item.inputComp->triggerCharacter == c)
              {
                getProxy().fire<event::TextInputUpdaterEventsOut<std::string>>(itemID, item.inputComp->input + "\n");
                item.inputComp->input.clear();
              }
              else
                item.inputComp->input += c;
              item.textComp->text = item.inputComp->input.c_str();
            }
          });
        break;
      case DefaultInputEvent::Type::REMOVE_CHAR:
        std::for_each(std::begin(_components), std::end(_components),
          [&ev, isBroadcast](auto& item)
          {
            if (!::isTextInputValidForUpdate(*item.inputStateComp))
              return ;

            if (isBroadcast || item.inputComp->textInputID == ev->getReceiverID())
            {
              component::removeLastChar(*item.inputComp);
              item.textComp->text = item.inputComp->input.c_str();
            }
          });
        break;
    }
  }
}
