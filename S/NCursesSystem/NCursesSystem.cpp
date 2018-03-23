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
    EntityManager::createEntity({std::make_shared<TerminalDrawable>("c\na"), std::make_shared<Transform>(0, 0, 0)});
  }

  int x = 0;
  for (auto& comp : _data)
  {
    mvprintw(comp.transform->getPosition().y,
             comp.transform->getPosition().x + x,
             comp.drawableComp->sym);
    ++x;
  }
  refresh();
}

void NCursesSystem::registerEntity(const EntityPtr& entity)
{
  NCursesData data;

  auto comps = entity->getComponents();
  for (auto& comp : comps)
  {
    if (comp->getID() == TerminalDrawable::getComponentID())
      data.drawableComp = std::static_pointer_cast<TerminalDrawable>(comp);
    else if (comp->getID() == Transform::getComponentID())
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
}

void NCursesSystem::atRemove()
{
  endwin();
  EManager::fire<CLISystemEvent>(CLISystemEvent::Type::ENABLE);
}
