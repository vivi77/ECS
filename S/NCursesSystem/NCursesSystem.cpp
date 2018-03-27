#include "NCursesSystem.hh"
#include "E/CLISystemEvent/CLISystemEvent.hh"
#include "E/EManager.hh"
#include <curses.h>
#include <algorithm>

#include "E/CoreEvent/CoreEvent.hh"
#include "Entity/EntityManager.hh"

namespace
{
  static constexpr TerminalDrawable::Color realColor[]{
    TerminalDrawable::Color::BLACK,
    TerminalDrawable::Color::RED,
    TerminalDrawable::Color::GREEN,
    TerminalDrawable::Color::YELLOW,
    TerminalDrawable::Color::BLUE,
    TerminalDrawable::Color::MAGENTA,
    TerminalDrawable::Color::CYAN,
    TerminalDrawable::Color::WHITE,
  };
  static constexpr int requestColor[]{
    static_cast<int>(TerminalDrawable::Color::BLACK),
    static_cast<int>(TerminalDrawable::Color::RED),
    static_cast<int>(TerminalDrawable::Color::GREEN),
    static_cast<int>(TerminalDrawable::Color::YELLOW),
    static_cast<int>(TerminalDrawable::Color::BLUE),
    static_cast<int>(TerminalDrawable::Color::MAGENTA),
    static_cast<int>(TerminalDrawable::Color::CYAN),
    static_cast<int>(TerminalDrawable::Color::WHITE),
  };
  static constexpr int colorValue[]{
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE,
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
} /* ! */

void NCursesSystem::exec()
{
  char c = getch();
  if (c == 'q')
    EManager::fire<CoreEvent>(CoreEvent::Type::EXIT);

  for (auto& comp : _data)
  {
    auto index = ::getIndexColorPair(comp.drawableComp->fgColor,
                                     comp.drawableComp->bgColor);
    attron(COLOR_PAIR(index));
    mvprintw(comp.transform->getPosition().y,
             comp.transform->getPosition().x,
             comp.drawableComp->sym);
    attroff(COLOR_PAIR(index));
  }
  refresh();
}

void NCursesSystem::registerEntity(const EntityPtr& entity)
{
  NCursesData data;

  auto comps = entity->getComponents();
  for (auto& comp : comps)
  {
    auto compID = comp->getID();
    if (compID == TerminalDrawable::getComponentID())
      data.drawableComp = std::static_pointer_cast<TerminalDrawable>(comp);
    else if (compID == Transform::getComponentID())
      data.transform = std::static_pointer_cast<Transform>(comp);
  }
  if (data.isValid())
    _data.emplace_back(data);
}

void NCursesSystem::setup()
{
  EManager::fire<CLISystemEvent>(CLISystemEvent::Type::DISABLE);
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  start_color();

  auto callback = [](const auto fg, const auto bg)
  {
    EntityManager::createEntity({std::make_shared<TerminalDrawable>("a", realColor[fg], realColor[bg]),
                                std::make_shared<Transform>(fg, bg, 0)});
  };
  ::execOnAllColor(callback);

  ::initNCursesColor();
}

void NCursesSystem::atRemove()
{
  endwin();
  EManager::fire<CLISystemEvent>(CLISystemEvent::Type::ENABLE);
}
