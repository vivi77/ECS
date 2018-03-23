#include "Transform.hh"

Transform::Transform(const float x, const float y, const float z)
  : _position{x, y, z}
{}

Transform::Transform(const Position& pos, const Rotation& rotation, const Scale& scale)
  : _position{pos}
  , _rotation{rotation}
  , _scale{scale}
{}
