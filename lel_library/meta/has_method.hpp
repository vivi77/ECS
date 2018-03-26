#pragma once

#include "has_base.hpp"

namespace lel
{
  namespace meta
  {
    namespace details
    {
      // It allows the checking of a inherited method
      // TODO: Check if it can see the adding of a method from a "middle" parent
      // class. Tests to add
      template <class NewBase, class MFP>
      struct change_base_of_member_fct_ptr;

      template <class NewBase, typename Base, typename R, typename ... Args>
      struct change_base_of_member_fct_ptr<NewBase, R (Base::*)(Args...) const>
      {
        using type = R (NewBase::*)(Args...) const;
      };

      template <class NewBase, typename Base, typename R, typename ... Args>
      struct change_base_of_member_fct_ptr<NewBase, R (Base::*)(Args...)>
      {
        using type = R (NewBase::*)(Args...);
      };

      template <class NewBase, class MFP>
      using change_base_of_member_fct_ptr_t = typename change_base_of_member_fct_ptr<NewBase, MFP>::type;
    } /* !details */
  } /* !meta */
} /* !lel */

//These macros can be used inside or outside class definition

// Works with classic method and static method
#define METACONCEPT_HAS_METHOD(name)\
  METACONCEPT_HAS_BASE(method, name, std::is_class_v<LHS>, int, Yes, lel::meta::details::change_base_of_member_fct_ptr_t<_LHS, decltype(&_LHS::name)>)

// Works only with classic method with or without specifier
// If you want to check type of a method with no specifier, you better use
// METACONCEPT_HAS_METHOD_TYPE_CHECK macro
#define METACONCEPT_HAS_METHOD_TYPE_CHECK_SPEC(name, ret, spec, ...)\
  METACONCEPT_HAS_BASE(method, name, std::is_class_v<LHS>, ret(LHS::*)(__VA_ARGS__) spec, R, lel::meta::details::change_base_of_member_fct_ptr_t<_LHS, decltype(&_LHS::name)>)

// Works only with static method with or without specifier (noexcept,...)
// If you want to check type of a method with no specifier, you better use
// METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK macro
#define METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK_SPEC(name, ret, spec, ...)\
  METACONCEPT_HAS_BASE(method, name, std::is_class_v<LHS>, ret(*)(__VA_ARGS__) spec, R, decltype(&_LHS::name))

// Works only with classic method without specifier (const, noexcept,...)
#define METACONCEPT_HAS_METHOD_TYPE_CHECK(name, ret, ...)\
  METACONCEPT_HAS_METHOD_TYPE_CHECK_SPEC(name, ret, , __VA_ARGS__)
  // Empty 3rd empty macro parameter expected (above)

// Works only with static method without specifier (noexcept,...)
#define METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK(name, ret, ...)\
  METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK_SPEC(name, ret, , __VA_ARGS__)
  // Empty 3rd empty macro parameter expected (above)


// ALIAS VERSION
#define METACONCEPT_HAS_METHOD_ALIAS(alias, name)\
  METACONCEPT_HAS_BASE(method, alias, std::is_class_v<LHS>, int, Yes, lel::meta::details::change_base_of_member_fct_ptr_t<_LHS, decltype(&_LHS::name)>)

#define METACONCEPT_HAS_METHOD_TYPE_CHECK_SPEC_ALIAS(alias, name, ret, spec, ...)\
  METACONCEPT_HAS_BASE(method, name, std::is_class_v<LHS>, ret(LHS::*)(__VA_ARGS__) spec, R, lel::meta::details::change_base_of_member_fct_ptr_t<_LHS, decltype(&_LHS::name)>)

#define METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK_SPEC_ALIAS(alias, name, ret, spec, ...)\
  METACONCEPT_HAS_BASE(method, alias, std::is_class_v<LHS>, ret(*)(__VA_ARGS__) spec, R, decltype(&_LHS::name))

#define METACONCEPT_HAS_METHOD_TYPE_CHECK_ALIAS(alias, name, ret, ...)\
  METACONCEPT_HAS_METHOD_TYPE_CHECK_SPEC_ALIAS(alias, name, ret, , __VA_ARGS__)

#define METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK_ALIAS(alias, name, ret, ...)\
  METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK_SPEC_ALIAS(alias, name, ret, , __VA_ARGS__)
