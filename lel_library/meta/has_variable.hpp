#pragma once

#include "has_base.hpp"

// Works for both attributes and static variables

#define METACONCEPT_HAS_VARIABLE(name)\
  METACONCEPT_HAS_BASE(variable, name, std::is_class_v<LHS>, int, Yes, decltype(_LHS::name))

#define METACONCEPT_HAS_VARIABLE_TYPE_CHECK(name, type)\
  METACONCEPT_HAS_BASE(variable, name, std::is_class_v<LHS>, type, R, decltype(_LHS::name))
