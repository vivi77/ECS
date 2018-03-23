#pragma once

#include "S/CRTPS.hpp"
#include "S/NCursesSystem/ncursessystem_export.h"
#include "C/TerminalDrawable/TerminalDrawable.hh"
#include "C/Transform/Transform.hh"
#include <vector>

class NCURSESSYSTEM_EXPORT NCursesSystem : public CRTPS<NCursesSystem>
{
public:
  using DrawablePtr = std::shared_ptr<TerminalDrawable>;
  using TransformPtr = std::shared_ptr<Transform>;

private:
  struct NCursesData
  {
    DrawablePtr drawableComp;
    TransformPtr transform;

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
  std::vector<NCursesData> _data;
};
