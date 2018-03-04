#pragma once

class IE
{
public:
  using ID = unsigned;

public:
  virtual ~IE() = default;
  virtual ID getID() const = 0;
};