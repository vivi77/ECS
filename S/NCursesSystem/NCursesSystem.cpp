#include "NCursesSystem.hh"
#include "E/CLISystemEvent/CLISystemEvent.hh"
#include "E/EManager.hh"
#include <curses.h>

#include "E/CoreEvent/CoreEvent.hh"
#include "Entity/EntityManager.hh"

void NCursesSystem::exec()
{
  char c = getch();
  if (c == 'q')
    EManager::fire<CoreEvent>(CoreEvent::Type::EXIT);
  else if (c == 'c')
  {
    EntityManager::createEntity({std::make_shared<TerminalDrawable>("c\na"),
                                std::make_shared<Transform>(0, 0, 0)});
  }

  for (auto& comp : _data)
  {
    attron(COLOR_PAIR(static_cast<int>(comp.drawableComp->fgColor)));
    mvprintw(comp.transform->getPosition().y,
             comp.transform->getPosition().x,
             comp.drawableComp->sym);
    attroff(COLOR_PAIR(static_cast<int>(comp.drawableComp->fgColor)));
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


  if (has_colors() == FALSE)
  {
    // Fire event to warn about the error OR create a component with information ?
    mvprintw(0, 0, "No colors");
    return;
  }
  init_pair(static_cast<int>(TerminalDrawable::Color::BLACK), COLOR_BLACK, 0);
  init_pair(static_cast<int>(TerminalDrawable::Color::RED), COLOR_RED, 0);
  init_pair(static_cast<int>(TerminalDrawable::Color::GREEN), COLOR_GREEN, 0);
  init_pair(static_cast<int>(TerminalDrawable::Color::YELLOW), COLOR_YELLOW, 0);
  init_pair(static_cast<int>(TerminalDrawable::Color::BLUE), COLOR_BLUE, 0);
  init_pair(static_cast<int>(TerminalDrawable::Color::MAGENTA), COLOR_MAGENTA, 0);
  init_pair(static_cast<int>(TerminalDrawable::Color::CYAN), COLOR_CYAN, 0);
  init_pair(static_cast<int>(TerminalDrawable::Color::WHITE), COLOR_WHITE, 0);
}

void NCursesSystem::atRemove()
{
  endwin();
  EManager::fire<CLISystemEvent>(CLISystemEvent::Type::ENABLE);
}
