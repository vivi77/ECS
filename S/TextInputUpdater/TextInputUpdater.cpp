#include "TextInputUpdater.hh"
#include "C/TextInput/TextInput.hh"
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
      //else if (compID == component::TextInputState::getComponentID())
        //;
    }
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
      switch (ev->getType())
      {
        case TIEventIn::Type::ADD_CHAR:
          std::for_each(std::begin(_components), std::end(_components),
            [&ev, this](auto& item)
            {
              const auto itemID = item.inputComp->getTextInputID();
              if (itemID == ev->getReceiverID())
              {
                const auto c = ev->getChar();
                if (item.inputComp->getTriggerCharacter() == c)
                  getProxy()->fire<TIEventOut>(itemID, item.inputComp->getInput());
                else
                  item.inputComp->addChar(c);
              }
            });
          break;
        case TIEventIn::Type::REMOVE_CHAR:
          std::for_each(std::begin(_components), std::end(_components),
            [&ev](auto& item)
            {
              if (item.inputComp->getTextInputID() == ev->getReceiverID())
                item.inputComp->removeLastChar();
            });
          break;
      }
    }
  }
}
