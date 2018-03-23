#pragma once

#include "C/Transform/transform_export.h"
#include "C/CRTPC.hpp"
#include "Utility/Vector3/Vector3.hh"

using Position = Vector3;
using Rotation = Vector3;
using Scale = Vector3;

struct TRANSFORM_EXPORT Transform : public CRTPC<Transform>
{
public:
  Transform(const float, const float, const float);
  Transform(const Position&, const Rotation&, const Scale&);
  virtual ~Transform() = default;

  Position getPosition() const;
  Rotation getRotation() const;
  Scale getScale() const;

  void setPosition(const Position&);
  void setRotation(const Rotation&);
  void setScale(const Scale&);

private:
  Position _position;
  Rotation _rotation;
  Scale _scale;
};
