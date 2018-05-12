#pragma once

#include "has_base.hpp"

// NOTE: Only used by the operator concepts.
// @param item: Can be changed to anything. Just an identifier.
//              ALTER the resulting name of created classes.
// @param name: Can be changed to anything. Just an identifier.
//              ALTER the resulting name of created classes.
// @param yes: Expected type of the test function. This cannot be the symbol
//             The template parameter 'LHS' and 'RHS' can be used which is the
//             type send as argument to the concept
// @param test_ret: Prefered value: Yes or R.
//                  Yes: Basic checking
//                  R: "Double checking". It will check that 'test_check' type
//                  and 'yes' type are the same.
//                  Type available: Yes, R, LHS/_LHS, RHS/_RHS, No
// @param ...: Chunk of code that will trigger SFINAE and check what you
//             want to check. MUST be a type.
//             decltype can be use.
//             Allow usage of comma in this chunk of code
//             The template parameter '_LHS' and '_RHS' can be used which is the
//             type send as argument to the concept. Be careful about the
//             underscore '_' in the name of parameters
#define METACONCEPT_HAS_BINARY_OP_BASE(item, name, yes, test_ret, ...)         \
  template <class LHS, class RHS>                                              \
  struct has_##item##_##name                                                   \
  {                                                                            \
  private:                                                                     \
    using Yes = yes;                                                           \
    struct No                                                                  \
    {                                                                          \
    };                                                                         \
                                                                               \
    template <typename _LHS, typename _RHS, typename R = __VA_ARGS__>          \
    static test_ret test(int);                                                 \
    template <typename, typename>                                              \
    static No test(...);                                                       \
                                                                               \
  public:                                                                      \
    static constexpr bool value = std::is_same_v<decltype(test<LHS, RHS>(0)), Yes>;\
  };                                                                           \
  template <class LHS, class RHS>                                              \
  static constexpr bool has_##item##_##name##_v =                              \
      has_##item##_##name<LHS, RHS>::value

#define METACONCEPT_HAS_BINARY_OPERATOR(name, test_check)\
  METACONCEPT_HAS_BINARY_OP_BASE(name, operator, int, Yes, test_check)

#define METACONCEPT_HAS_BINARY_OPERATOR_TYPE_CHECK(name, test_check, ret, ...)\
  METACONCEPT_HAS_BINARY_OP_BASE(name, operator, ret(LHS::*)(__VA_ARGS__), R, test_check)

#define METACONCEPT_HAS_UNARY_OPERATOR(name, test_check)\
  METACONCEPT_HAS_BASE(name, operator, true, int, Yes, test_check)

#define METACONCEPT_HAS_UNARY_OPERATOR_TYPE_CHECK(name, test_check, ret, ...)\
  METACONCEPT_HAS_BASE(name, operator, true, ret(LHS::*)(__VA_ARGS__), R, test_check)

namespace lel
{
  namespace meta
  {
    namespace details
    {
      // Turn anything into an lvalue reference.
      // Necessary for operators (mainly assign operators) which need an lvalue
      // at the left side of the operation
      template <typename T>
      struct to_lvalue_ref
      {
        using type =
            std::conditional_t<std::negation_v<std::is_lvalue_reference<T>>,
                               std::add_lvalue_reference_t<std::decay_t<T>>,
                               T>;
      };
      template <typename T>
      using to_lvalue_ref_t = typename to_lvalue_ref<T>::type;
    } /* !details */

    // Overloadable assign operators
    METACONCEPT_HAS_BINARY_OPERATOR(assign, decltype(std::declval<details::to_lvalue_ref_t<_LHS>>() = std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(plus_assign, decltype(std::declval<details::to_lvalue_ref_t<_LHS>>() += std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(minus_assign, decltype(std::declval<details::to_lvalue_ref_t<_LHS>>() -= std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(multiply_assign, decltype(std::declval<details::to_lvalue_ref_t<_LHS>>() *= std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(division_assign, decltype(std::declval<details::to_lvalue_ref_t<_LHS>>() /= std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(modulo_assign, decltype(std::declval<details::to_lvalue_ref_t<_LHS>>() %= std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(and_assign, decltype(std::declval<details::to_lvalue_ref_t<_LHS>>() &= std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(or_assign, decltype(std::declval<details::to_lvalue_ref_t<_LHS>>() |= std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(xor_assign, decltype(std::declval<details::to_lvalue_ref_t<_LHS>>() ^= std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(leftshift_assign, decltype(std::declval<details::to_lvalue_ref_t<_LHS>>() <<= std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(rightshift_assign, decltype(std::declval<details::to_lvalue_ref_t<_LHS>>() >>= std::declval<_RHS>()));

    // Comparison operators
    METACONCEPT_HAS_BINARY_OPERATOR(equal, decltype(std::declval<_LHS>() == std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(not_equal, decltype(std::declval<_LHS>() != std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(greater, decltype(std::declval<_LHS>() > std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(greater_equal, decltype(std::declval<_LHS>() >= std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(less, decltype(std::declval<_LHS>() < std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(less_equal, decltype(std::declval<_LHS>() <= std::declval<_RHS>()));
#if 0 //__cplusplus > // c++20 macro
    METACONCEPT_HAS_BINARY_OPERATOR(three_way, decltype(std::declval<_LHS>() <=> std::declval<_RHS>()));
#endif

    // Arithmetic operators
    METACONCEPT_HAS_UNARY_OPERATOR(unary_plus, decltype(+std::declval<_LHS>()));
    METACONCEPT_HAS_UNARY_OPERATOR(unary_minus, decltype(-std::declval<_LHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(addition, decltype(std::declval<_LHS>() + std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(subtraction, decltype(std::declval<_LHS>() - std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(multiplication, decltype(std::declval<_LHS>() * std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(division, decltype(std::declval<_LHS>() / std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(modulo, decltype(std::declval<_LHS>() % std::declval<_RHS>()));
    METACONCEPT_HAS_UNARY_OPERATOR(bit_not, decltype(&_LHS::operator~));
    METACONCEPT_HAS_BINARY_OPERATOR(bit_and, decltype(std::declval<_LHS>() & std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(bit_or, decltype(std::declval<_LHS>() | std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(bit_xor, decltype(std::declval<_LHS>() ^ std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(leftshift, decltype(std::declval<_LHS>() << std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(rightshift, decltype(std::declval<_LHS>() >> std::declval<_RHS>()));

    // Logical operators
    METACONCEPT_HAS_UNARY_OPERATOR(neg, decltype(&_LHS::operator!));
    METACONCEPT_HAS_BINARY_OPERATOR(logic_and, decltype(std::declval<_LHS>() && std::declval<_RHS>()));
    METACONCEPT_HAS_BINARY_OPERATOR(logic_or, decltype(std::declval<_LHS>() || std::declval<_RHS>()));

    // Increment/Decrement operators
    METACONCEPT_HAS_UNARY_OPERATOR(pre_increment, decltype(++std::declval<_LHS>()));
    METACONCEPT_HAS_UNARY_OPERATOR(pre_decrement, decltype(--std::declval<_LHS>()));
    METACONCEPT_HAS_UNARY_OPERATOR(post_increment, decltype(std::declval<_LHS>()++));
    METACONCEPT_HAS_UNARY_OPERATOR(post_decrement, decltype(std::declval<_LHS>()--));

    // Memver access operators
    METACONCEPT_HAS_UNARY_OPERATOR(indirection, decltype(*std::declval<_LHS>()));
    METACONCEPT_HAS_UNARY_OPERATOR(address_of, decltype(&std::declval<details::to_lvalue_ref_t<_LHS>>()));
    METACONCEPT_HAS_BINARY_OPERATOR(member_pointer_indirection, decltype(std::declval<_LHS>()->*std::declval<_RHS>()));
  } /* !meta */
} /* !lel */
