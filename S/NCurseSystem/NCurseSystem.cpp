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
  //for (auto& comp : _drawableComp)
  //{
  //  attron();
  //  mvprintw(comp->pos.y, comp->pos.x, comp->str);
  //  attroff();
  //}
  char c = getch();
  if (c == 'q')
    EManager::fire<CoreEvent>(CoreEvent::Type::EXIT);
  else if (c == 'c')
    EntityManager::createEntity({std::make_shared<CompTerminalDrawable>("c")});
}

void NCurseSystem::registerEntity(const EntityPtr&)
{
  //NCurseData data;

  //auto comps = entity->getComponents();
  //for (auto& comp : comps)
  //{
    //if (comp->getID() == CompTerminalDrawable::getComponentID())
      //data.drawableComp = std::static_pointer_cast<CompTerminalDrawable>(comp);
  //}
  //if (data.isValid())
    //_drawableComp.emplace_back(data);
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
