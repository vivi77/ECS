#pragma once

#include "IE.hh"
#include <memory>

class IEListener
{
public:
  using EPtr = std::shared_ptr<IE>;

public:
  virtual ~IEListener() = default;
  virtual void update(const EPtr&) = 0;
};
