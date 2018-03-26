#include "ML_Data.hh"
#include <iostream>

namespace ml
{
  Data::Data(const double value, const double gradient)
    : mValue{value}
    , mGradient{gradient}
  {
    ;
  }

  Data& Data::operator+=(const Data& rhs) noexcept
  {
    mValue += rhs.mValue;
    return (*this);
  }

  Data& Data::operator-=(const Data& rhs) noexcept
  {
    mValue -= rhs.mValue;
    return (*this);
  }

  Data& Data::operator*=(const Data& rhs) noexcept
  {
    mValue *= rhs.mValue;
    return (*this);
  }

  Data& Data::operator/=(const Data& rhs) noexcept
  {
    mValue /= rhs.mValue;
    return (*this);
  }

  bool Data::operator==(const Data& rhs) noexcept
  {
    return (mValue == rhs.mValue && mGradient == rhs.mGradient);
  }
} /* !ml */

ml::Data operator+(const ml::Data& lhs, const ml::Data& rhs) noexcept
{
  ml::Data cpy{lhs};
  cpy += rhs;
  return (cpy);
}

ml::Data operator-(const ml::Data& lhs, const ml::Data& rhs) noexcept
{
  ml::Data cpy{lhs};
  cpy -= rhs;
  return (cpy);
}

ml::Data operator*(const ml::Data& lhs, const ml::Data& rhs) noexcept
{
  ml::Data cpy{lhs};
  cpy *= rhs;
  return (cpy);
}

ml::Data operator/(const ml::Data& lhs, const ml::Data& rhs) noexcept
{
  ml::Data cpy{lhs};
  cpy /= rhs;
  return (cpy);
}

std::ostream& operator<<(std::ostream& s, const ml::Data& rhs)
{
  s << "{ 'value': " << rhs.getValue();
  s << ", 'gradient': " << rhs.getGradient() << " }";
  return (s);
}
