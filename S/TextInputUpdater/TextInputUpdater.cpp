#include "TextInputUpdater.hh"
#include "E/IE.hh"
#include "E/IDEvent.hh"
#include "E/TextInputUpdaterEvents/TextInputUpdaterEventsIn.hpp"
#include "E/TextInputUpdaterEvents/TextInputUpdaterEventsOut.hpp"

namespace lel::ecs::system
{
  TextInputUpdater::TextInputUpdater(std::unique_ptr<CoreProxy>& proxy)
    : CRTPS{proxy}
  {
  }

  void TextInputUpdater::exec()
  {
  }

  void TextInputUpdater::registerEntity(const EntityPtr& entity)
  {
    Item item;
    auto comps = entity->getComponents();
    for (auto& comp : comps)
    {
      const auto compID = comp->getID();
      if (compID == component::TextInputStr::getComponentID())
        item.inputComp = std::static_pointer_cast<component::TextInputStr>(comp);
      else if (compID == component::TerminalText::getComponentID())
        item.textComp = std::static_pointer_cast<component::TerminalText>(comp);
      //else if (compID == component::TextInputState::getComponentID())
        //;
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
    const auto it = std::find_if(std::begin(_components), std::end(_components), pred);
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
    using TIEventOut = event::TextInputUpdaterEventsOut<std::string>;

    if (ptr->getID() == TIEventIn::getEventID())
    {
      const auto ev = std::static_pointer_cast<TIEventIn>(ptr);
      const bool isBroadcast = ev->getReceiverID().empty();
      switch (ev->getType())
      {
        case TIEventIn::Type::ADD_CHAR:
          std::for_each(std::begin(_components), std::end(_components),
            [&ev, isBroadcast, this](auto& item)
            {
              const auto itemID = item.inputComp->textInputID;
              if (isBroadcast || itemID == ev->getReceiverID())
              {
                const auto c = ev->getChar();
                if (item.inputComp->triggerCharacter == c)
                  getProxy()->fire<TIEventOut>(itemID, item.inputComp->input);
                else
                {
                  item.inputComp->input += c;
                  item.textComp->text = item.inputComp->input.c_str();
                }
              }
            });
          break;
        case TIEventIn::Type::REMOVE_CHAR:
          std::for_each(std::begin(_components), std::end(_components),
            [&ev, isBroadcast](auto& item)
            {
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
}
