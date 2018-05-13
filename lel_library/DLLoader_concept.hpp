#pragma once

#include "meta/type_traits_has.hpp"

namespace lel
{
  namespace concept
  {
    template <typename T, bool auto_check = true>
    struct DLLoader
    {
      METACONCEPT_HAS_ALIAS(Handle);
      METACONCEPT_HAS_ALIAS(Symbol);
      METACONCEPT_HAS_ALIAS(LoadOption);
      using Handle = has_alias_Handle_t<T>;
      using Symbol = has_alias_Symbol_t<T>;
      using LoadOption = has_alias_LoadOption_t<T>;

      METACONCEPT_HAS_VARIABLE(NULL_HANDLE);
      METACONCEPT_HAS_VARIABLE(lastError);

      METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK_SPEC(loadLibrary, Handle, noexcept, const char*, const LoadOption);
      METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK_SPEC(unloadLibrary, void, noexcept, Handle);
      METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK_SPEC(getSymbol, Symbol, noexcept, Handle, const char*);
      METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK(getLastError, const char*);
      METACONCEPT_HAS_STATIC_METHOD_TYPE_CHECK_SPEC(isLibraryLoaded, bool, noexcept, const char*);

      static constexpr bool value = []()
      {
        if constexpr (auto_check)
        {
          static_assert(has_alias_Handle_v<T>, "concept::DLLoader: Missing 'Handle' alias");
          static_assert(has_alias_Symbol_v<T>, "concept::DLLoader: Missing 'Symbol' alias");
          static_assert(has_alias_LoadOption_v<T>, "concept::DLLoader: Missing 'LoadOption' alias");
          static_assert(has_method_loadLibrary_v<T>, "concept::DLLoader: Missing 'loadLibrary(const char*, const LoadOption)' static method");
          static_assert(has_method_unloadLibrary_v<T>, "concept::DLLoader: Missing 'unloadLibrary' static method");
          static_assert(has_method_getSymbol_v<T>, "concept::DLLoader: Missing 'getSymbol' static method");
          static_assert(has_method_getLastError_v<T>, "concept::DLLoader: Missing 'getLastError' static method");
          static_assert(has_method_getLastError_v<T>, "concept::DLLoader: Missing 'isLibraryLoaded' static method");
          static_assert(has_variable_NULL_HANDLE_v<T>, "concept::DLLoader: Missing 'NULL_HANDLE' static variable");
          static_assert(has_variable_lastError_v<T>, "concept::DLLoader: Missing 'lastError' static variable");
        }
        return has_alias_Handle_v<T> &&
          has_alias_Symbol_v<T> &&
          has_alias_LoadOption_v<T> &&
          has_method_loadLibrary_v<T> &&
          has_method_unloadLibrary_v<T> &&
          has_method_getSymbol_v<T> &&
          has_method_getLastError_v<T> &&
          has_method_isLibraryLoaded_v<T> &&
          has_variable_NULL_HANDLE_v<T> &&
          has_variable_lastError_v<T>;
        // TODO: Found a way to determine if there is a template function
        //    --> Maybe impossible except if we target a specific templated
        //        function
        //has_method_convertSymbol_v<T>;
      }();
    };
  } /* !concept */
} /* !lel */
