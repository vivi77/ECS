#pragma once

class IC
{
public:
  using ID = unsigned;

public:
  virtual ~IC() = default;
  virtual ID getID() const = 0;
};
