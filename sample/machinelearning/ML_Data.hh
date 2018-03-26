#pragma once

#include <iostream>

namespace ml
{
  /** @brief Data class for machine learning
   */
  class Data
  {
  public:
    Data() = default;
    Data(const double value, const double gradient);
    Data(const Data&) = default;
    Data(Data&&) = default;
    ~Data() = default;

    Data& operator=(const Data&) = default;
    Data& operator=(Data&&) = default;

    /** @brief Get data value
     */
    double getValue() const noexcept
    {
      return (mValue);
    }

    /** @brief Get data gradient
     */
    double getGradient() const noexcept
    {
      return (mGradient);
    }

    /** @brief Set data value
     *
     *  @param value New value
     */
    void setValue(const double value) noexcept
    {
      mValue = value;
    }

    /** @brief Set data gradient
     *
     *  @param gradient New gradient value
     */
    void setGradient(const double gradient) noexcept
    {
      mGradient = gradient;
    }

    /** @brief Add to the data value, its gradient multiplied by a factor value
     *
     *  @param factor Factor to apply on the gradient before the addition
     */
    void applyGradient(const double factor) noexcept
    {
      mValue += mGradient * factor;
    }

    Data& operator+=(const Data& rhs) noexcept;
    Data& operator-=(const Data& rhs) noexcept;
    Data& operator*=(const Data& rhs) noexcept;
    Data& operator/=(const Data& rhs) noexcept;

    bool operator==(const Data& rhs) noexcept;

  private:
    double mValue; /**< Value */
    double mGradient; /**< Tug force value */
  };
} /* !ml */

ml::Data operator+(const ml::Data& lhs, const ml::Data& rhs) noexcept;
ml::Data operator-(const ml::Data& lhs, const ml::Data& rhs) noexcept;
ml::Data operator*(const ml::Data& lhs, const ml::Data& rhs) noexcept;
ml::Data operator/(const ml::Data& lhs, const ml::Data& rhs) noexcept;
std::ostream& operator<<(std::ostream& s, const ml::Data& rhs);
