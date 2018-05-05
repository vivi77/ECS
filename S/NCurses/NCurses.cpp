#include "NCurses.hh"
#include "S/CoreProxy/CoreProxy.hh"
#include "C/Transform/Transform.hpp"
#include "E/CLISystemEvent/CLISystemEvent.hh"
#include "E/EManager/EManager.hh"
#include "Utility/Bresenham.hpp"
#include <curses.h>
#include <algorithm>

#include "E/CoreEvent/CoreEvent.hh"
#include "Entity/EntityManager.hh"
#include "C/TextInput/TextInput.hh"

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
} /* ! */

namespace lel::ecs::system
{
  NCurses::NCurses(std::unique_ptr<CoreProxy>& proxy)
    : CRTPS{proxy}
  {}

  void NCurses::exec()
  {
    char c = getch();
    if (c == 'q')
      getProxy()->fire<event::CoreEvent>(event::CoreEvent::Type::EXIT);
    else if (c == 'd')
      getProxy()->destroyEntity(0);

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
      if (nbSegment > 2)
      {
        const auto& p1 = comp.polygon->points[nbSegment - 1];
        const auto& p2 = comp.polygon->points[0];
        lel::graphic::drawLine(p1.x, p1.y, p2.x, p2.y, drawCallback);
      }

      toggleOffAttributes();
      attroff(COLOR_PAIR(index));
    }

    refresh();
  }

  void NCurses::registerEntity(const EntityPtr& entity)
  {
    NCursesData data;

    static int counter = 0;

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
      else if (compID == component::TextInputStr::getComponentID())
      {
        ++counter;
        mvprintw(40, 40, (std::to_string(counter) + " " + std::to_string(compID) + " " + std::to_string(entity->getID())).c_str());
      }
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
    getProxy()->fire<event::CLISystemEvent>(event::CLISystemEvent::Type::DISABLE);
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    if (start_color() == OK)
    {
      auto callback = [this](const auto fg, const auto bg, const auto attr)
      {
        auto draw = std::make_shared<component::TerminalText>(
          "a", realColor[fg], realColor[bg], termattr[attr]);
        auto transform = std::make_shared<NCTransform>(fg * 8 + attr, bg, 0);
        getProxy()->createEntity({draw, transform});
      };
      ::execOnColorsAndAttr(callback);
      ::initNCursesColor();
    }

    // Text input test
    auto textInput = std::make_shared<component::TextInputStr>("system input");
    getProxy()->createEntity({textInput});

    // Straight line test
    std::vector<Vector2<int>> pts{{0, 0}, {0, 3}, {3, 3}, {3, 0}};
    auto poly = std::make_shared<component::TerminalPolygon>(pts);
    auto transform = std::make_shared<NCTransform>(20, 20, 0);
    getProxy()->createEntity({poly, transform});

    //'Perfect' Diagonale line test
    pts = {{0, -2}, {2, 0}, {0, 2}, {-2, 0}};
    poly = std::make_shared<component::TerminalPolygon>(pts);
    transform = std::make_shared<NCTransform>(28, 20, 0);
    getProxy()->createEntity({poly, transform});

    // Slight rotation line test
    pts = {{3, 0}, {0, 1}, {1, 4}, {4, 3}};
    poly = std::make_shared<component::TerminalPolygon>(pts, TerminalColor::Color::RED);
    transform = std::make_shared<NCTransform>(36, 20, 0);
    getProxy()->createEntity({poly, transform});
  }

  void NCurses::atRemove()
  {
    endwin();
    getProxy()->fire<event::CLISystemEvent>(event::CLISystemEvent::Type::ENABLE);
  }
} /* !lel::ecs::system */
