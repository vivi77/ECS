#pragma once

#include "CRTPE.hpp"
#include "coreevent_export.h"
#include <string>

class COREEVENT_EXPORT CoreEvent : public CRTPE<CoreEvent>
{
public:
  enum class Type : char
  {
    UNKNOWN,
    EXIT,
    ADD_SYSTEM,
    REM_SYSTEM,
  };

public:
  CoreEvent(Type t = Type::UNKNOWN);
  CoreEvent(Type t, const std::string& data);
  virtual ~CoreEvent() = default;

  Type getType() const;
  std::string getData() const;

  void setType(const Type type);
  void setData(const std::string& data);

private:
  Type _type = Type::UNKNOWN;
  std::string _data;
};
