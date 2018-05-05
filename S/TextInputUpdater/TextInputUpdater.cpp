#include "TextInputUpdater.hh"
#include "C/TextInput/TextInput.hh"
#include "E/IE.hh"
#include "E/IDEvent.hh"

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
    //if (ptr->getID() == event::TextInputUpdaterEventIn::getEventID())
    //{
    //  const auto ev = std::static_pointer_cast<event::TextInputUpdaterEventIn>(ptr);
    //  switch (ev->getType())
    //  {
    //    case event::TextInputUpdaterEventIn::Type::ADD_CHAR:
    //    std::for_each(std::begin(_components), std::end(_components),
    //      [&ev](auto& item)
    //      {
    //        const auto itemID = item.inputComp->getTextInputID();
    //        if (itemID == ev->getReceiverID())
    //        {
    //          const auto c = ev->getChar();
    //          if (item.getTriggerCharacter() == c)
    //            EManager::fire<TextInputUpdaterEventOut>(itemID);
    //          else
    //            item.addChar(c);
    //        }
    //      });
    //      break;
    //    case event::TextInputUpdaterEventIn::Type::REMOVE_CHAR:
    //      std::for_each(std::begin(_components), std::end(_components)),
    //      [&ev](auto& item)
    //      {
    //        if (item.inputComp->getTextInputID() == ev->getReceiverID())
    //          item.removeChar();
    //      }
    //      break;
    //  }
    //}
  }
}
