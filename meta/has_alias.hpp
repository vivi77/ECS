#pragma once

#include "has_base.hpp"

#define METACONCEPT_HAS_ALIAS(name)                                            \
  METACONCEPT_HAS_BASE(alias, name, std::is_class_v<LHS>, int, Yes, typename _LHS::name);            \
  template <class LHS, bool = has_alias_##name##_v<LHS>>                       \
  struct has_alias_##name##_type                                               \
  {                                                                            \
    using type = typename LHS::name;                                           \
  };                                                                           \
  template <class LHS>                                                         \
  struct has_alias_##name##_type<LHS, false>                                   \
  {                                                                            \
    using type = int;                                                          \
  };                                                                           \
  template <class LHS>                                                         \
  using has_alias_##name##_t = typename has_alias_##name##_type<LHS>::type;

// Choose int as the default type of has_alias_##name##_type
//  So it can be used on the contrary of void
