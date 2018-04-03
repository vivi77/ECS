#pragma once

namespace lel::ecs
{
  template <typename T = float>
  struct Vector2
  {
    T x;
    T y;
  };

  template <typename T = float>
  struct Vector3
  {
    T x;
    T y;
    T z;
  };

  template <typename T>
  Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs)
  {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
  }
} /* !lel::ecs */
