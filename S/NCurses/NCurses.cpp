#include "NCurses.hh"
#include "E/CLISystemEvent/CLISystemEvent.hh"
#include "E/TextInputUpdaterEvents/TextInputUpdaterEventsIn.hpp"
#include "C/TextInput/TextInput.hh"
#include "C/TextInput/TextInputState.hh"
#include "Utility/Bresenham.hpp"
#include <curses.h>
#include <algorithm>

ECS_CREATE_IDSYSTEM(NCurses)

namespace
{
  using TerminalDrawable = lel::ecs::component::TerminalText;
  using TerminalColor = lel::ecs::component::TerminalColor;

  constexpr TerminalColor::Color realColor[]{
    TerminalColor::Color::BLACK,
    TerminalColor::Color::RED,
    TerminalColor::Color::GREEN,
    TerminalColor::Color::YELLOW,
    TerminalColor::Color::BLUE,
    TerminalColor::Color::MAGENTA,
    TerminalColor::Color::CYAN,
    TerminalColor::Color::WHITE,
  };
  constexpr int requestColor[]{
    static_cast<int>(TerminalColor::Color::BLACK),
    static_cast<int>(TerminalColor::Color::RED),
    static_cast<int>(TerminalColor::Color::GREEN),
    static_cast<int>(TerminalColor::Color::YELLOW),
    static_cast<int>(TerminalColor::Color::BLUE),
    static_cast<int>(TerminalColor::Color::MAGENTA),
    static_cast<int>(TerminalColor::Color::CYAN),
    static_cast<int>(TerminalColor::Color::WHITE),
  };
  constexpr int colorValue[]{
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE,
  };
  constexpr int realAttr[]{
    A_BOLD,
    A_DIM,
    A_UNDERLINE,
    A_BLINK,
    A_REVERSE,
    A_INVIS,
  };
  constexpr TerminalColor::Attributes termattr[]{
    TerminalColor::Attributes::BOLD,
    TerminalColor::Attributes::DIM,
    TerminalColor::Attributes::UNDERLINED,
    TerminalColor::Attributes::BLINK,
    TerminalColor::Attributes::REVERSE,
    TerminalColor::Attributes::HIDDEN,
  };

  int getColorValue(const TerminalDrawable::Color color)
  {
    auto i = -1;
    auto pred = [&i, &color](const auto it) -> bool
    {
      ++i;
      return it == color;
    };
    // No error possible
    std::find_if(realColor, realColor + sizeof(realColor) / sizeof(*realColor), pred);
    return i;
  }

  int generateIndexColorPair(const int fg, const int bg)
  {
    // index 0 is reserved ==> 1 + ...
    return 1 + fg * (sizeof(requestColor) / sizeof(*requestColor)) + bg;
  }

  int getIndexColorPair(const TerminalDrawable::Color fg, const TerminalDrawable::Color bg)
  {
    return ::generateIndexColorPair(::getColorValue(fg), ::getColorValue(bg));
  }

  template <typename Fct>
  void execOnAllColor(Fct&& fct)
  {
    constexpr auto nbColor = sizeof(requestColor) / sizeof(*requestColor);
    for (auto fg = 0ul; fg < nbColor; ++fg)
    {
      for (auto bg = 0ul; bg < nbColor; ++bg)
        std::forward<Fct>(fct)(fg, bg);
    }
  }

  template <typename Fct>
  void execOnColorsAndAttr(Fct&& fct)
  {
    constexpr auto nbColor = sizeof(requestColor) / sizeof(*requestColor);
    constexpr auto nbAttr = sizeof(termattr) / sizeof(*termattr);
    for (auto fg = 0ul; fg < nbColor; ++fg)
    {
      for (auto bg = 0ul; bg < nbColor; ++bg)
      {
        for (auto attr = 0ul; attr < nbAttr; ++attr)
          std::forward<Fct>(fct)(fg, bg, attr);
      }
    }
  }

  void initNCursesColor()
  {
    if (has_colors() == FALSE)
    {
      // Fire event to warn about the error OR create a component with information ?
      mvprintw(0, 0, "No colors");
      return;
    }

    auto callback = [](const auto fg, const auto bg)
    {
      int index = ::generateIndexColorPair(fg, bg);
      init_pair(index, colorValue[fg], colorValue[bg]);
    };
    ::execOnAllColor(callback);
  }

  template <size_t N>
  void toggleOnAttributes(const std::bitset<N>& attr)
  {
    for (auto i = 0ul; i < N; ++i)
    {
      if (attr.test(i))
        attron(realAttr[i]);
    }
  }

  void toggleOffAttributes()
  {
    attrset(A_NORMAL);
  }

  void testNCursesAttributes(lel::ecs::CoreProxy& proxy)
  {
    if (start_color() == OK)
    {
      auto callback = [&proxy](const auto fg, const auto bg, const auto attr)
      {
        auto draw = std::make_shared<lel::ecs::component::TerminalText>(
          "a", realColor[fg], realColor[bg], termattr[attr]);
        auto transform = std::make_shared<lel::ecs::system::NCurses::NCTransform>(fg * 8 + attr, bg, 0);
        proxy.createEntity({draw, transform});
      };
      ::execOnColorsAndAttr(callback);
      ::initNCursesColor();
    }
  }

  void testNCursesSystemExecution(lel::ecs::CoreProxy& proxy)
  {
    // Straight line test
    std::vector<lel::ecs::Vector2<int>> pts{{0, 0}, {0, 3}, {3, 3}, {3, 0}};
    auto poly = std::make_shared<lel::ecs::component::TerminalPolygon>(pts);
    auto transform = std::make_shared<lel::ecs::system::NCurses::NCTransform>(20, 20, 0);
    proxy.createEntity({poly, transform});

    //'Perfect' Diagonale line test
    pts = {{0, -2}, {2, 0}, {0, 2}, {-2, 0}};
    poly = std::make_shared<lel::ecs::component::TerminalPolygon>(pts);
    transform = std::make_shared<lel::ecs::system::NCurses::NCTransform>(28, 20, 0);
    proxy.createEntity({poly, transform});

    // Slight rotation line test
    pts = {{3, 0}, {0, 1}, {1, 4}, {4, 3}};
    poly = std::make_shared<lel::ecs::component::TerminalPolygon>(pts, TerminalColor::Color::RED);
    transform = std::make_shared<lel::ecs::system::NCurses::NCTransform>(36, 20, 0);
    proxy.createEntity({poly, transform});
  }

  void testNCursesTextInput(lel::ecs::CoreProxy& proxy)
  {
    auto textInput = std::make_shared<lel::ecs::component::TextInputStr>("input");
    textInput->triggerCharacter = '\n';
    auto inputPoly = std::make_shared<lel::ecs::component::TerminalPolygon>(
      std::vector<lel::ecs::Vector2<int>>{{0, 0}, {0, 2}, {10, 2}, {10, 0}}
    );
    auto inputTrans = std::make_shared<lel::ecs::system::NCurses::NCTransform>(40, 30, 0);
    auto inputText = std::make_shared<lel::ecs::component::TerminalText>("");
    auto inputTextState = std::make_shared<lel::ecs::component::TextInputState>(true, true);

    proxy.createEntity({textInput, inputPoly, inputTrans, inputText, inputTextState});

    auto input2 = std::make_shared<lel::ecs::component::TextInputStr>("input2");
    input2->triggerCharacter = '\n';
    auto poly2 = std::make_shared<lel::ecs::component::TerminalPolygon>(
      std::vector<lel::ecs::Vector2<int>>{{0, 0}, {0, 2}, {10, 2}, {10, 0}}
    );
    auto trans2 = std::make_shared<lel::ecs::system::NCurses::NCTransform>(40, 33, 0);
    auto text2 = std::make_shared<lel::ecs::component::TerminalText>("");
    auto state2 = std::make_shared<lel::ecs::component::TextInputState>(false, true);
    proxy.createEntity({input2, poly2, trans2, text2, state2});

    auto input3 = std::make_shared<lel::ecs::component::TextInputStr>("input3");
    input3->triggerCharacter = '\n';
    auto poly3 = std::make_shared<lel::ecs::component::TerminalPolygon>(
      std::vector<lel::ecs::Vector2<int>>{{0, 0}, {0, 2}, {10, 2}, {10, 0}}
    );
    auto trans3 = std::make_shared<lel::ecs::system::NCurses::NCTransform>(40, 36, 0);
    auto text3 = std::make_shared<lel::ecs::component::TerminalText>("");
    auto state3 = std::make_shared<lel::ecs::component::TextInputState>(true, false);
    proxy.createEntity({input3, poly3, trans3, text3, state3});

    auto input4 = std::make_shared<lel::ecs::component::TextInputStr>("input4");
    input4->triggerCharacter = '\n';
    auto poly4 = std::make_shared<lel::ecs::component::TerminalPolygon>(
      std::vector<lel::ecs::Vector2<int>>{{0, 0}, {0, 2}, {10, 2}, {10, 0}}
    );
    auto trans4 = std::make_shared<lel::ecs::system::NCurses::NCTransform>(40, 39, 0);
    auto text4 = std::make_shared<lel::ecs::component::TerminalText>("");
    auto state4 = std::make_shared<lel::ecs::component::TextInputState>(false, false);
    proxy.createEntity({input4, poly4, trans4, text4, state4});
  }
} /* ! */

namespace lel::ecs::system
{
  NCurses::NCurses(CoreProxy& proxy)
    : CRTPS{proxy}
  {}

  void NCurses::exec()
  {
    char c = getch();
    switch (c)
    {
      case 127: // Delete character
        getProxy().fire<event::TextInputUpdaterEventsIn<std::string>>("");
        clear();
        break;
      case ERR: break; //Ignored
      default:
        getProxy().fire<event::TextInputUpdaterEventsIn<std::string>>("", c);
    }

    for (const auto& comp : _polygon)
    {
      auto index = ::getIndexColorPair(comp.polygon->fgColor, comp.polygon->bgColor);
      attron(COLOR_PAIR(index));
      toggleOnAttributes(comp.polygon->attributes);

      const auto nbSegment = comp.polygon->points.size();
      if (nbSegment <= 1)
        continue;

      auto drawCallback =
      [&comp](const int x, const int y, const lel::graphic::CircleLocation)
      {
        mvprintw(y + comp.transform->position.y,
                 x + comp.transform->position.x,
                 "*");
      };
      for (auto i = 0ul; i < nbSegment - 1; ++i)
      {
        const auto& p1 = comp.polygon->points[i];
        const auto& p2 = comp.polygon->points[i + 1];
        lel::graphic::drawLine(p1.x, p1.y, p2.x, p2.y, drawCallback);
      }
      // Draw the last line of the polygon
      if (nbSegment > 2)
      {
        const auto& p1 = comp.polygon->points[nbSegment - 1];
        const auto& p2 = comp.polygon->points[0];
        lel::graphic::drawLine(p1.x, p1.y, p2.x, p2.y, drawCallback);
      }

      toggleOffAttributes();
      attroff(COLOR_PAIR(index));
    }

    for (const auto& comp : _text)
    {
      auto index = ::getIndexColorPair(comp.text->fgColor, comp.text->bgColor);
      attron(COLOR_PAIR(index));
      toggleOnAttributes(comp.text->attributes);
      mvprintw(comp.transform->position.y,
               comp.transform->position.x,
               comp.text->text);
      toggleOffAttributes();
      attroff(COLOR_PAIR(index));
    }

    refresh();
  }

  void NCurses::registerEntity(const EntityPtr& entity)
  {
    NCursesData data;

    auto comps = entity->getComponents();
    for (auto& comp : comps)
    {
      auto compID = comp->getID();
      if (compID == component::TerminalText::getComponentID())
        data.text = std::static_pointer_cast<component::TerminalText>(comp);
      else if (compID == NCTransform::getComponentID())
        data.transform = std::static_pointer_cast<NCTransform>(comp);
      else if (compID == component::TerminalPolygon::getComponentID())
        data.polygon = std::static_pointer_cast<component::TerminalPolygon>(comp);
    }

    if (data.isValidText())
      _text.emplace_back(data);

    if (data.isValidPolygon())
      _polygon.emplace_back(data);
  }

  void NCurses::deregisterEntity(const EntityPtr& entity)
  {
    auto end = std::end(_text);
    const auto pred = [&entity](auto& it)
    {
      return it.transform->getEntityOwnerID() == entity->getID();
    };
    auto it = std::find_if(std::begin(_text), std::end(_text), pred);
    if (it != end)
      _text.erase(it);

    end = std::end(_polygon);
    it = std::find_if(std::begin(_polygon), end, pred);
    if (it != end)
      _polygon.erase(it);

    // To properly erase the deleted element
    clear();
  }

  void NCurses::setup()
  {
    getProxy().fire<event::CLISystemEvent>(event::CLISystemEvent::Type::DISABLE);
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    testNCursesAttributes(getProxy());
    testNCursesSystemExecution(getProxy());
    testNCursesTextInput(getProxy());
  }

  void NCurses::atRemove()
  {
    endwin();
    getProxy().fire<event::CLISystemEvent>(event::CLISystemEvent::Type::ENABLE);
  }
} /* !lel::ecs::system */
