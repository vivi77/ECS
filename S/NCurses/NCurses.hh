#pragma once

#include "S/CRTPS.hpp"
#include "C/TerminalComponents/Text.hh"
#include "C/TerminalComponents/Polygon.hh"
#include "C/Transform/Transform.hpp"
#include <vector>

namespace lel::ecs::system
{
  class NCurses : public CRTPS<NCurses>
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
    NCurses(CoreProxy& proxy);
    ~NCurses() override = default;

    void exec() override;
    void registerEntity(const EntityPtr&) override;
    void deregisterEntity(const EntityPtr&) override;
    void setup() override;
    void atRemove() override;

  private:
    Container<NCursesData> _text;
    Container<NCursesData> _polygon;

  public:
    static constexpr std::string_view name{"NCurses"};
  };
} /* !lel::ecs::system */
