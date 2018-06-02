#pragma once

#include "E/CRTPE.hpp"
#include <variant>
#include <string>

namespace lel::ecs::event
{
  class EManagerEvent : public CRTPE<EManagerEvent>
  {
  public:
    using Data = std::variant<std::string, ID>;

  public:
    enum class Type : char
    {
      // OK
      LISTENER_ADDED,
      LISTENER_REMOVED,
      EVENT_ADDED,

      // ERROR
      NOT_LISTENER,
      LISTENER_NOT_FOUND,
      LISTENER_ALREADY_ADDED,
      EVENT_ALREADY_ADDED,
      EVENT_DTOR_NOT_FOUND,
    };

  public:
    EManagerEvent(const Type t);
    template <typename T>
    EManagerEvent(const Type t, T&& data)
      : _t{t}
      , _data{std::forward<T>(data)}
    {}
    ~EManagerEvent() override = default;

    Type getType() const;
    Data getData() const;

  private:
    Type _t;
    Data _data;
  };
} /* !lel::ecs::event */
