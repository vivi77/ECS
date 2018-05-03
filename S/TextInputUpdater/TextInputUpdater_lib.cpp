#include "TextInputUpdater.hh"
#include "S/TextInputUpdater/textinputupdater_export.h"

extern "C"
{
  TEXTINPUTUPDATER_EXPORT lel::ecs::system::IS* create(lel::ecs::CoreProxy* proxy)
  {
    std::unique_ptr<lel::CoreProxy> proxyPtr{proxy};
    return new lel::ecs::system::TextInputUpdater>(proxyPtr);
  }

  TEXTINPUTUPDATER_EXPORT void destroy(lel::ecs::system::IS* ptr)
  {
    delete ptr;
  }
}
