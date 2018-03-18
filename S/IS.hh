#pragma once

class IS
{
public:
  using ID = unsigned;

public:
  virtual ~IS() = default;
  virtual void exec() = 0;
  virtual ID getID() const = 0;
  virtual bool isListener() const = 0;
};
