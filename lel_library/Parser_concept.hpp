#pragma once

#include "type_traits_has.hpp"

namespace lel
{
  namespace concept
  {
    template <class T, bool auto_check = true>
    struct InputProducer
    {
      METACONCEPT_HAS_ALIAS(Output);
      METACONCEPT_HAS_ALIAS(Type);
      METACONCEPT_HAS_ALIAS(Precedence);
      using Output = has_alias_Output_t<T>;
      using Type = has_alias_Type_t<T>;
      using Precedence = has_alias_Precedence_t<T>;

      METACONCEPT_HAS_METHOD_TYPE_CHECK(parseExpression, Output, const Precedence);
      METACONCEPT_HAS_METHOD_TYPE_CHECK(reset, void);
      METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK(getOutputType, Type, const Output&);

      static constexpr bool value = []()
      {
        if constexpr (auto_check)
        {
          static_assert(has_alias_Output_v<T>, "concept::InputProducer: Missing 'Output' type alias");
          static_assert(has_alias_Type_v<T>, "concept::InputProducer: Missing 'Type' type alias");
          static_assert(has_alias_Precedence_v<T>, "concept::InputProducer: Missing 'Precedence' type alias");
          static_assert(has_method_parseExpression_v<T>, "concept::InputProducer: Missing 'parseExpression()' method");
          static_assert(has_method_reset_v<T>, "concept::InputProducer: Missing 'reset()' method");
          static_assert(has_method_getOutputType_v<T>, "concept::InputProducer: Missing 'getOutputType()' static method");
        }
        return true;
      }();
    };

    template <class T, bool auto_check = true>
    struct ParserPolicy
    {
      METACONCEPT_HAS_ALIAS(Precedence);
      METACONCEPT_HAS_ALIAS(Output);
      using Precedence = has_alias_Precedence_t<T>;

      METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK(getDefaultPrecedence, Precedence);

      static constexpr bool value = []()
      {
        if constexpr (auto_check)
        {
          static_assert(has_alias_Precedence_v<T>, "concept::ParserPolicy: Missing 'Precedence' type alias");
          static_assert(has_alias_Output_v<T>, "concept::ParserPolicy: Missing 'Output' type alias");
          static_assert(has_method_getDefaultPrecedence_v<T>, "concept::ParserPolicy: Missing 'getDefaultPrecedence()' static method");
        }
        return has_alias_Precedence_v<T> &&
          has_alias_Output_v<T> &&
          has_method_getDefaultPrecedence_v<T>;
      }();
    };
  }
}
