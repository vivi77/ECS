#include "NCurseSystem.hh"
#include "E/CLISystemEvent/CLISystemEvent.hh"
#include "E/EManager.hh"
#include "C/CompTerminalDrawable/CompTerminalDrawable.hh"
#include <curses.h>

#include "E/CoreEvent/CoreEvent.hh"
#include "Entity/EntityManager.hh"
//#include "C/CManager/CManager.hh"

void NCurseSystem::exec()
{
  char c = getch();
  if (c == 'q')
    EManager::fire<CoreEvent>(CoreEvent::Type::EXIT);
  else if (c == 'c')
  {
    EntityManager::createEntity({std::make_shared<CompTerminalDrawable>("c\na")});
  }

  int x = 0;
  for (auto& comp : _drawableComp)
  {
    mvprintw(comp.drawableComp->pos.y, comp.drawableComp->pos.x + x, comp.drawableComp->sym);
    ++x;
  }
  refresh();
}

void NCurseSystem::registerEntity(const EntityPtr& entity)
{
  NCurseData data;

  auto comps = entity->getComponents();
  for (auto& comp : comps)
  {
    if (comp->getID() == CompTerminalDrawable::getComponentID())
      data.drawableComp = std::static_pointer_cast<CompTerminalDrawable>(comp);
  }
  if (data.isValid())
    _drawableComp.emplace_back(data);
  refresh();
}

void NCurseSystem::setup()
{
  EManager::fire<CLISystemEvent>(CLISystemEvent::Type::DISABLE);
  initscr();
  cbreak();
  noecho();
}

void NCurseSystem::atRemove()
{
  endwin();
  EManager::fire<CLISystemEvent>(CLISystemEvent::Type::ENABLE);
}
