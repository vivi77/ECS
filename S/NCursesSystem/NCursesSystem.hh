#pragma once

#include "S/CRTPS.hpp"
#include "S/NCursesSystem/ncursessystem_export.h"
#include "C/TerminalDrawable/TerminalDrawable.hh"
#include <vector>

class NCURSESSYSTEM_EXPORT NCursesSystem : public CRTPS<NCursesSystem>
{
public:
  using DrawablePtr = std::shared_ptr<TerminalDrawable>;

private:
  struct NCursesData
  {
    DrawablePtr drawableComp;

    bool isValid() const
    {
      return drawableComp != nullptr;
    }
  };

public:
  virtual ~NCursesSystem() = default;

  void exec() override;
  void registerEntity(const EntityPtr&) override;
  void setup() override;
  void atRemove() override;

private:
  std::vector<NCursesData> _drawableComp;
};
