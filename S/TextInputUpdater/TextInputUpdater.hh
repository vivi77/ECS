#pragma once

#include "S/CRTPS.hpp"
#include "E/TextInputUpdaterEvents/TextInputUpdaterEventsIn.hpp"
#include "E/TextInputUpdaterEvents/TextInputUpdaterEventsOut.hpp"
#include "E/IEListener.hh"
#include "C/TextInput/TextInput.hh"
#include "C/TextInput/TextInputState.hh"
#include "C/TerminalComponents/Text.hh"

namespace lel::ecs::system
{
  class TextInputUpdater : public CRTPS<TextInputUpdater>, public event::IEListener
  {
  public:
    using TextInputCompPtr = std::shared_ptr<component::TextInputStr>;
    using TextCompPtr = std::shared_ptr<component::TerminalText>;
    using TextInputStatePtr = std::shared_ptr<component::TextInputState>;

    using DefaultInputEvent = event::TextInputUpdaterEventsIn<std::string>;
    using DefaultOutputEvent = event::TextInputUpdaterEventsOut<std::string>;

  public:
    struct Item
    {
      TextInputCompPtr inputComp = nullptr;
      TextCompPtr textComp = nullptr;
      TextInputStatePtr inputStateComp = nullptr;

      bool isValid() const
      {
        return inputComp != nullptr && textComp != nullptr && inputStateComp != nullptr;
      }
    };

  public:
    TextInputUpdater(CoreProxy& proxy);
    ~TextInputUpdater() override = default;
    void exec() override;
    void registerEntity(const EntityPtr&) override;
    void deregisterEntity(const EntityPtr&) override;
    void setup() override;
    void atRemove() override;

    void update(const EPtr&) override;

  private:
    void basicUpdate(const std::shared_ptr<DefaultInputEvent>& ev);

  private:
    std::vector<Item> _components;
  };
} /* !lel::ecs::system */
