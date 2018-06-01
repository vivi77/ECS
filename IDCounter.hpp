#pragma once

namespace lel::ecs::utility
{
  template <class D, typename T>
  class IDCounter
  {
  public:
    IDCounter(const T vl)
      : _value{vl}
    {}
    IDCounter(const IDCounter&) = default;

    T getValue() const
    {
      return _value;
    }

    D& operator++()
    {
      ++_value;
      return static_cast<D&>(*this);
    }

    D& operator--()
    {
      --_value;
      return static_cast<D&>(*this);
    }

    D operator++(int)
    {
      T keep = _value++;
      return D{keep};
    }

    D operator--(int)
    {
      T keep = _value--;
      return D{keep};
    }

    operator T()
    {
      return _value;
    }

    operator T() const
    {
      return _value;
    }

  private:
    T _value = 0;
  };
} /* !lel::ecs::utility */
