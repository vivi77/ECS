#pragma once

namespace lel::ecs::utility
{
  template <typename T>
  class IDCounter
  {
  public:
    IDCounter(const T vl)
      : _value{vl}
    {}

    T getValue() const
    {
      return _value;
    }

    IDCounter& operator++()
    {
      ++_value;
      return *this;
    }

    IDCounter& operator--()
    {
      --_value;
      return *this;
    }

  private:
    T _value;
  };
} /* !lel::ecs::utility */
