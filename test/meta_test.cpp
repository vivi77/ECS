#include "gtest/gtest.h"
#include "type_traits_has.hpp"
#include "conditional_os.hpp"
#include <map>
#include <bitset>

//TODO: Check if a deleted function is considered as a missing operator

namespace
{
  class Dummy
  {
  friend Dummy& operator*=(Dummy& lhs, const int) { return lhs; }
  friend Dummy& operator/=(Dummy& lhs, const int) { return lhs; }
  friend Dummy& operator%=(Dummy& lhs, const int) { return lhs; }
  friend Dummy& operator>>=(Dummy& lhs, const Dummy&) { return lhs; }
  friend Dummy& operator<<=(Dummy& lhs, const Dummy&) { return lhs; }
  friend bool operator&&(const Dummy&, const Dummy&) { return true; }
  friend bool operator||(const Dummy&, const Dummy&) { return true; }
  friend void* operator&(Dummy) = delete;
  friend void operator->*(Dummy, int) {}
  };

  class BOO
  {
  public:
    enum class Titi {};

    void lol();
    void foo();
    int bar(Titi, double, std::map<int, int>);
    static double* hey(int);

    // Should not be the same as the concept (see BOOConcept class)
    void barError();
    static void heyError();

    using FOO = BOO;

    int a1;
    static int a2;
    static short b;
  };

  class BOOBOO : public BOO {};

  template <typename T>
  struct BOOConcept
  {
    METACONCEPT_HAS_METHOD(lol);
    METACONCEPT_HAS_METHOD_TYPE_CHECK(foo, void);
    METACONCEPT_HAS_METHOD_TYPE_CHECK(bar, int, BOO::Titi, double, std::map<int, int>);
    METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK(hey, double*, int);

    static constexpr bool has_lol_v = has_method_lol_v<T>;
    static constexpr bool has_foo_v = has_method_foo_v<T>;
    static constexpr bool has_bar_v = has_method_bar_v<T>;
    static constexpr bool has_hey_v = has_method_hey_v<T>;
    static constexpr bool value = has_lol_v && has_foo_v && has_bar_v && has_hey_v;

    // Unit tests for when human errors come into the play
    METACONCEPT_HAS_METHOD_TYPE_CHECK(barError, int, unsigned);
    METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK(heyError, int, double);
    static constexpr bool has_barError_v = has_method_barError_v<T>;
    static constexpr bool has_heyError_v = has_method_heyError_v<T>;
  };

  template <typename T>
  struct BOOConcept_alias
  {
    METACONCEPT_HAS_ALIAS(FOO);
    static constexpr bool value = has_alias_FOO<T>::value;
  };

  template <typename T>
  struct BOOConcept_var
  {
    METACONCEPT_HAS_VARIABLE(a1);
    METACONCEPT_HAS_VARIABLE(a2);
    METACONCEPT_HAS_VARIABLE_TYPE_CHECK(b, short);
    METACONCEPT_HAS_VARIABLE(FOO); //Check that FOO is not considered as a variable. It should be an type alias

    static constexpr bool value =
      has_variable_a1_v<T> &&
      has_variable_a2_v<T> &&
      has_variable_b_v<T>;
  };
} /* ! */

TEST(meta, conditional_os_value)
{
#ifdef __linux__
  int expect = 1;
  int unexpect = 2;
#elif _WIN32
  int expect = 2;
  int unexpect = 1;
#endif
  auto v = lel::meta::conditional_os<int>{expect, unexpect}.value;
  EXPECT_TRUE(v == expect);
}

TEST(meta, basic_has_operator)
{
  bool v;

  v = lel::meta::has_assign_operator_v<std::string, std::string>;
  EXPECT_TRUE(v);
  v = lel::meta::has_assign_operator_v<std::string, std::vector<int>>;
  EXPECT_FALSE(v);

  v = lel::meta::has_plus_assign_operator_v<int, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_plus_assign_operator_v<std::string, std::vector<int>>;
  EXPECT_FALSE(v);

  v = lel::meta::has_minus_assign_operator_v<int, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_minus_assign_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_multiply_assign_operator_v<Dummy, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_multiply_assign_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_division_assign_operator_v<Dummy, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_division_assign_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_modulo_assign_operator_v<Dummy, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_modulo_assign_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_and_assign_operator_v<int, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_and_assign_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_or_assign_operator_v<unsigned long long, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_or_assign_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_xor_assign_operator_v<short, short>;
  EXPECT_TRUE(v);
  v = lel::meta::has_xor_assign_operator_v<double, double>;
  EXPECT_FALSE(v);

  v = lel::meta::has_leftshift_assign_operator_v<Dummy, Dummy>;
  EXPECT_TRUE(v);
  v = lel::meta::has_leftshift_assign_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_rightshift_assign_operator_v<Dummy, Dummy>;
  EXPECT_TRUE(v);
  v = lel::meta::has_rightshift_assign_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_equal_operator_v<std::string, std::string>;
  EXPECT_TRUE(v);
  v = lel::meta::has_equal_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_not_equal_operator_v<std::vector<int>, std::vector<int>>;
  EXPECT_TRUE(v);
  v = lel::meta::has_not_equal_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_greater_operator_v<double, double>;
  EXPECT_TRUE(v);
  v = lel::meta::has_greater_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_greater_equal_operator_v<int, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_greater_equal_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  using K = std::map<int, int>::key_type;
  v = lel::meta::has_less_operator_v<K, K>;
  EXPECT_TRUE(v);
  v = lel::meta::has_less_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_less_equal_operator_v<K, K>;
  EXPECT_TRUE(v);
  v = lel::meta::has_less_equal_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_addition_operator_v<std::vector<int>::iterator, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_addition_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_subtraction_operator_v<double, double>;
  EXPECT_TRUE(v);
  v = lel::meta::has_subtraction_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_multiplication_operator_v<int, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_multiplication_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_division_operator_v<int, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_division_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_modulo_operator_v<unsigned, unsigned>;
  EXPECT_TRUE(v);
  v = lel::meta::has_modulo_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  EXPECT_TRUE(lel::meta::has_bit_not_operator_v<std::bitset<1>>);
  v = lel::meta::has_bit_not_operator_v<std::vector<int>>;
  EXPECT_FALSE(v);

  using B = std::bitset<1>;
  v = lel::meta::has_bit_and_operator_v<B, B>;
  EXPECT_TRUE(v);
  v = lel::meta::has_bit_and_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_bit_or_operator_v<B, B>;
  EXPECT_TRUE(v);
  v = lel::meta::has_bit_or_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_bit_xor_operator_v<B, B>;
  EXPECT_TRUE(v);
  v = lel::meta::has_bit_xor_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_leftshift_operator_v<std::bitset<1>, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_leftshift_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_rightshift_operator_v<std::bitset<1>, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_rightshift_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  EXPECT_TRUE(lel::meta::has_neg_operator_v<std::ostream>);
  v = lel::meta::has_neg_operator_v<std::string>;
  EXPECT_FALSE(v);

  v = lel::meta::has_logic_and_operator_v<Dummy, Dummy>;
  EXPECT_TRUE(v);
  v = lel::meta::has_logic_and_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  v = lel::meta::has_logic_or_operator_v<Dummy, Dummy>;
  EXPECT_TRUE(v);
  v = lel::meta::has_logic_or_operator_v<std::string, int>;
  EXPECT_FALSE(v);

  EXPECT_TRUE(lel::meta::has_pre_increment_operator_v<std::vector<int>::iterator>);
  v = lel::meta::has_pre_increment_operator_v<std::string>;
  EXPECT_FALSE(v);

  EXPECT_TRUE(lel::meta::has_pre_decrement_operator_v<std::vector<int>::iterator>);
  v = lel::meta::has_pre_decrement_operator_v<std::string>;
  EXPECT_FALSE(v);

  EXPECT_TRUE(lel::meta::has_post_increment_operator_v<std::vector<int>::iterator>);
  v = lel::meta::has_post_increment_operator_v<std::string>;
  EXPECT_FALSE(v);

  EXPECT_TRUE(lel::meta::has_post_decrement_operator_v<std::vector<int>::iterator>);
  v = lel::meta::has_post_decrement_operator_v<std::string>;
  EXPECT_FALSE(v);

  EXPECT_TRUE(lel::meta::has_unary_plus_operator_v<int>);
  v = lel::meta::has_unary_plus_operator_v<std::string>;
  EXPECT_FALSE(v);

  EXPECT_TRUE(lel::meta::has_unary_minus_operator_v<double>);
  v = lel::meta::has_unary_minus_operator_v<std::string>;
  EXPECT_FALSE(v);

  EXPECT_TRUE(lel::meta::has_indirection_operator_v<int*>);
  v = lel::meta::has_indirection_operator_v<std::string>;
  EXPECT_FALSE(v);

  EXPECT_TRUE(lel::meta::has_address_of_operator_v<int>);
  v = lel::meta::has_address_of_operator_v<Dummy>;
  EXPECT_FALSE(v);

  v = lel::meta::has_member_pointer_indirection_operator_v<Dummy, int>;
  EXPECT_TRUE(v);
  v = lel::meta::has_member_pointer_indirection_operator_v<std::string, int>;
  EXPECT_FALSE(v);

#if 0 //__cplusplus > //c++20 macro
  EXPECT_TRUE(lel::meta::has_three_way_operator_v<std::string>);
  v = lel::meta::has_three_way_operator_v<std::string, int>;
  EXPECT_FALSE(v);
#endif
}

TEST(meta, has_method)
{
  EXPECT_TRUE(BOOConcept<BOO>::value);
  EXPECT_FALSE(BOOConcept<int>::value);
  EXPECT_FALSE(BOOConcept<BOO>::has_barError_v);
  EXPECT_FALSE(BOOConcept<BOO>::has_heyError_v);
}

TEST(meta, has_alias)
{
  EXPECT_TRUE(BOOConcept_alias<BOO>::value);
  EXPECT_FALSE(BOOConcept_alias<int>::value);
}

TEST(meta, has_variable)
{
  EXPECT_TRUE(BOOConcept_var<BOO>::value);
  EXPECT_FALSE(BOOConcept_var<BOO>::has_variable_FOO_v<BOO>);
  EXPECT_FALSE(BOOConcept_var<int>::value);
}

TEST(meta, has_inherited_X)
{
  EXPECT_TRUE(BOOConcept<BOOBOO>::value);
  EXPECT_TRUE(BOOConcept_alias<BOO>::value);
  EXPECT_TRUE(BOOConcept_var<BOO>::value);
}
