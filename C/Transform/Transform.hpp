#pragma once

#include "C/CRTPC.hpp"
#include "Utility/Vector.hpp"

namespace lel::ecs::component
{
  template <typename T>
  struct Transform : public CRTPC<Transform<T>>
  {
    using Position = Vector3<T>;
    using Rotation = Vector3<T>;
    using Scale = Vector3<T>;

  public:
    Transform(const T x, const T y, const T z)
      : position{x, y, z}
    {}
    Transform(const Position& pos, const Rotation& rot, const Scale& sc)
      : position{pos}
      , rotation{rot}
      , scale{sc}
    {}
    ~Transform() override = default;

  public:
    Position position;
    Rotation rotation;
    Scale scale;

  public:
    constexpr static std::string_view name = "Transform";
  };
} /* !lel */
