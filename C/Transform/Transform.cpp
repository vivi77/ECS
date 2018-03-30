#include "Transform.hh"

namespace lel
{
  namespace ecs
  {
    namespace component
    {
      Transform::Transform(const float x, const float y, const float z)
        : _position{x, y, z}
      {}

      Transform::Transform(const Position& pos, const Rotation& rotation, const Scale& scale)
        : _position{pos}
        , _rotation{rotation}
        , _scale{scale}
      {}

      Position Transform::getPosition() const
      {
        return _position;
      }

      Rotation Transform::getRotation() const
      {
        return _rotation;
      }

      Scale Transform::getScale() const
      {
        return _scale;
      }

      void Transform::setPosition(const Position& position)
      {
        _position = position;
      }

      void Transform::setRotation(const Rotation& rotation)
      {
        _rotation = rotation;
      }

      void Transform::setScale(const Scale& scale)
      {
        _scale = scale;
      }
    } /* !component */
  } /* !ecs */
} /* !lel */
