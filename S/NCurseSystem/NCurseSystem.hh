#pragma once

#include "CRTPS.hpp"
#include "ncursesystem_export.h"
//#include "C/CompDrawable.hh"
#include <vector>

class NCURSESYSTEM_EXPORT NCurseSystem : public CRTPS<NCurseSystem>
{
public:
  //using CompDrawablePtr = std::shared_ptr<CompDrawable>;
  //
  //private:
  //  struct NCurseData
  //  {
  //    CompDrawablePtr drawableComp;
  //
  //    bool isValid()
  //    {
  //      return drawableComp != nullptr;
  //    }
  //  };

public:
  virtual ~NCurseSystem() = default;

  void exec() override;
  void registerEntity(const EntityPtr&) override;

private:
  //std::vector<NCurseData> _drawableComp;
};
