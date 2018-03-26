# meta

Lel's metaprogramming utilities classes.

## Content

Mostly type\_traits that check classes **PUBLIC** content.
type\_traits\_has.hpp contains all the other has\_\* header files.
All the has\_\* header files has macros that generate type\_traits class that
suit your need.

  * has\_base: Base macro for all other has\_\* type\_traits.
  * has\_alias: Check whether a type is in a class. Inherited types are included.
  * has\_method: Check whether a method is in a class. Either member and static methods and inherited method.
  * has\_operator: Check whether there is an overload of an operator between two types.
  * has\_variable: Check whether a variable with a specific name is in a class.

## has\_\*

#### Usage

Include any of these header files and you will have access to macros named `METACONCEPT_HAS_<thing_to_check>` (except for has\_operator)
These macros can be included anywhere, in the global scope, in a namespace or in a class definition.

They all take as first parameter the name of what you check.
For example, if you want to check a variable named 'fooBar' then call the following macro `METACONCEPT_HAS_VARIABLE(fooBar);`
It will generate a template class named `has_variable_fooBar`.

These template will always have a `value` field. HAS\_ALIAS also have a `type` field.
The macros also provide a \*\_v variable and \*\_t type alias.

#### Example

```
// Example 1
class Foo
{
  METACONCEPT_HAS_METHOD(blob);

  // or has_method_blob_v<Foo>
  static_assert(has_method_blob<Foo>::value);
};

// Example 2
METACONCEPT_HAS_METHOD(toto);
void foo()
{
  if constexpr (has_method_toto_v<Foo>)
    std::cout << "Foo does not have a method named 'toto'\n";
  else
  {
    Foo f;
    f.toto();
  }
}

// Example 3
template <class T>
struct ConceptFoo
{
  METACONCEPT_HAS_METHOD_TYPE_CHECK(bar, int, std::string);
  METACONCEPT_HAS_ALIAS(babar);

  static constexpr bool value = has_method_bar_v<T> && has_alias_babar_v<T>;
};

static_assert(ConceptFoo<Foo>::value);

// Example 4
template <class T, bool auto_check = true>
struct ConceptBar
{
  METACONCEPT_HAS_METHOD_TYPE_CHECK_SPEC(bar, void, noexcept);
  METACONCEPT_HAS_VARIABLE(babar);

  static constexpr bool value = []()
  {
    if constexpr (auto_check)
    {
      static_assert(has_method_bar_v<T>, "Missing 'bar'");
      static_assert(has_alias_babar_v<T>, "Missing 'babar'");
    }
    return has_method_bar_v<T> && has_alias_babar_v<T>;
  }();
};
```

#### Recap

Macro                      | \_v | \_t | TYPE\_CHECK |
---------------------------|-----------|-------------|
METACONCEPT\_HAS\_BASE     |  O  |  X  |      X      |
METACONCEPT\_HAS\_ALIAS    |  O  |  O  |      X      |
METACONCEPT\_HAS\_METHOD\_\* |  O  |  X  |      O      |
METACONCEPT\_HAS\_VARIABLE |  O  |  X  |      O      |

## conditional\_os

A class which choose the 1st value or the 2nd according to the OS.
**This works only with Linux and Windows**
**No optimization. It will create the 2 values at runtime**.
It just hides the usage of the preprocessor macros.

#### Usage

You just have to give the type of the data you want this class to select.
Then give your 2 values to the constructor of this class.
The 1st value will be choose if the OS is Linux, else it chooses the 2nd value if the OS is Windows.
**If it neither of those 2 OS, this class THROWS !!!**

#### Example

```
void main()
{
  std::cout << "You are using this code on " << lel::conditional_os<std::string>("Linux", "Windows") << "\n";
  return 0;
}
```
