#pragma once

#include <type_traits>

// @param item: Can be changed to anything. Just an identifier.
//              ALTER the resulting name of created classes.
// @param name: Can be changed to anything. Just an identifier.
//              ALTER the resulting name of created classes.
// @param pre_test: Condition that can be used to instantly exclude some types
//                  from the checking. Main use is to exclude primitive types
//                  from the checking (because it is not a class)
//                  The template parameter 'LHS' can be used which is the type
//                  send as argument to the concept
// @param yes: Expected type of the test function. This cannot be the symbol
//             The template parameter 'LHS' can be used which is the type send
//             as argument to the concept
// @param test_ret: Prefered value: Yes or R.
//                  Yes: Basic checking
//                  R: "Double checking". It will check that 'test_check' type
//                  and 'yes' type are the same.
// @param ...: Chunk of code that will trigger SFINAE and check what you
//             want to check. MUST be a type.
//             decltype can be use.
//             Allow usage of comma in this chunk of code
//             The template parameter '_LHS' can be used which is the type send
//             as argument to the concept. Be careful about the underscore '_'
//             in the name of parameter
#define METACONCEPT_HAS_BASE(item, name, pre_test, yes, test_ret, ...)         \
  template <class LHS, bool = pre_test>                                        \
  struct has_##item##_##name                                                   \
  {                                                                            \
    static constexpr bool value = false;                                       \
  };                                                                           \
  template <class LHS>                                                         \
  struct has_##item##_##name<LHS, true>                                        \
  {                                                                            \
  private:                                                                     \
    using Yes = yes;                                                           \
    struct No                                                                  \
    {                                                                          \
    };                                                                         \
                                                                               \
    template <typename _LHS, typename R = __VA_ARGS__>                         \
    static test_ret test(int);                                                 \
    template <typename>                                                        \
    static No test(...);                                                       \
                                                                               \
  public:                                                                      \
    static constexpr bool value = std::is_same_v<decltype(test<LHS>(0)), Yes>; \
  };                                                                           \
  template <class LHS>                                                         \
  static constexpr bool has_##item##_##name##_v =                              \
      has_##item##_##name<LHS>::value
