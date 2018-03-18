#pragma once

#include "CRTPE.hpp"
#include "emanagerevent_export.h"
#include <variant>
#include <string>

class EMANAGEREVENT_EXPORT EManagerEvent : public CRTPE<EManagerEvent>
{
public:
  using Data = std::variant<ID, std::string>;

public:
  enum class Type : char
  {
    UNKNOWN,
    // OK
    LISTENER_ADDED,
    LISTENER_REMOVED,
    EVENT_ADDED,

    // ERROR
    NOT_LISTENER,
    LISTENER_NOT_FOUND,
    LISTENER_ALREADY_ADDED,
    EVENT_ALREADY_ADDED,
  };

public:
  EManagerEvent(const Type t = Type::UNKNOWN);
  template <typename T>
  EManagerEvent(const Type t, T&& data)
    : _t{t}
    , _data{std::forward<T>(data)}
  {}
  virtual ~EManagerEvent() = default;

  Type getType() const;
  Data getData() const;

private:
  Type _t = Type::UNKNOWN;
  Data _data;
};
