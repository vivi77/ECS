#pragma once

#include "CRTPE.hpp"
#include "emanagerevent_export.h"

class EMANAGEREVENT_EXPORT EManagerEvent : public CRTPE<EManagerEvent>
{
  using ID = unsigned; //SIDGenerate::ID

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
  };

public:
  EManagerEvent(const Type t = Type::UNKNOWN);
  EManagerEvent(const Type t, ID id);
  virtual ~EManagerEvent() = default;

  Type getType() const;
  ID getIdData() const;

private:
  Type _t = Type::UNKNOWN;
  ID _idData = 0;
};
