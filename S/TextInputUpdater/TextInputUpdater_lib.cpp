#include "TextInputUpdater.hh"
#include "S/TextInputUpdater/textinputupdater_export.h"
#include "S/CoreProxy/CoreProxy.hh"

extern "C"
{
  TEXTINPUTUPDATER_EXPORT lel::ecs::system::IS* create(lel::ecs::CoreProxy& proxy)
  {
    return new lel::ecs::system::TextInputUpdater(proxy);
  }

  TEXTINPUTUPDATER_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}
