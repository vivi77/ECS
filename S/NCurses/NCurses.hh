#pragma once

#include "S/CRTPS.hpp"
#include "S/NCurses/ncursessystem_export.h"
#include "C/TerminalComponents/Text.hh"
#include "C/TerminalComponents/Polygon.hh"
#include <vector>

// NCurses specific forward declaration
// In C++, It is not possible to fast forward type-alias
namespace lel::ecs::component
{
  template <class T> struct Transform;
} /* !lel::ecs::component */

namespace lel::ecs::system
{
  class NCURSESSYSTEM_EXPORT NCurses : public CRTPS<NCurses>
  {
  public:
    template <typename T> using Container = std::vector<T>;
    using NCTransform = component::Transform<int>;

  public:
    using TextPtr = std::shared_ptr<component::TerminalText>;
    using TransformPtr = std::shared_ptr<NCTransform>;
    using PolygonPtr = std::shared_ptr<component::TerminalPolygon>;

  private:
    struct NCursesData
    {
      TransformPtr transform = nullptr;
      TextPtr text = nullptr;
      PolygonPtr polygon = nullptr;

      bool isValidPolygon() const
      {
        return polygon != nullptr && transform != nullptr;
      }

      bool isValidText() const
      {
        return text != nullptr && transform != nullptr;
      }

      bool isValid() const
      {
        return (text != nullptr || polygon != nullptr) && transform != nullptr;
      }
    };

  public:
    virtual ~NCurses() = default;

    void exec() override;
    void registerEntity(const EntityPtr&) override;
    void setup() override;
    void atRemove() override;

  private:
    Container<NCursesData> _text;
    Container<NCursesData> _polygon;

  public:
    static constexpr std::string_view name{"NCurses"};
  };
} /* !lel::ecs::system */
