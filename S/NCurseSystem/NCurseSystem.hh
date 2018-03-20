#pragma once

#include "S/CRTPS.hpp"
#include "S/NCurseSystem/ncursesystem_export.h"
#include "C/CompTerminalDrawable/CompTerminalDrawable.hh"
#include <vector>

class NCURSESYSTEM_EXPORT NCurseSystem : public CRTPS<NCurseSystem>
{
public:
  using DrawablePtr = std::shared_ptr<CompTerminalDrawable>;

private:
  struct NCurseData
  {
    DrawablePtr drawableComp;

    bool isValid() const
    {
      return drawableComp != nullptr;
    }
  };

public:
  virtual ~NCurseSystem() = default;

  void exec() override;
  void registerEntity(const EntityPtr&) override;

private:
  std::vector<NCurseData> _drawableComp;
};
