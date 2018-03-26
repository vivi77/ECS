#pragma once

#include "ML_Circuit.hh"

namespace ml
{
  /** @brief Support Vector Machine
   */
  class SVM : public ml::Circuit
  {
  public:
    SVM() = default;
    SVM(const SVM&) = default;
    SVM(SVM&&) = default;
    virtual ~SVM() = default;

    SVM& operator=(const SVM&) = default;
    SVM& operator=(SVM&&) = default;
  };
} /* !ml */
