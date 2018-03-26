#pragma once

#if defined(SYS_LINUX) || defined(SYS_WINDOWS)
# error "This file cannot be included because macro SYS_LINUX or SYS_WINDOWS are already defined"
#endif

#ifdef __linux__
# define SYS_LINUX      true
# define SYS_WINDOWS    false
#elif _WIN32
# define SYS_LINUX      false
# define SYS_WINDOWS    true
#endif

#include <utility>
#include <stdexcept>

namespace lel
{
  namespace meta
  {
    // Convert macro into constexpr values
    // Does not pollute preprocessors symbol
    static constexpr const auto is_linux_v = SYS_LINUX;
    static constexpr const auto is_windows_v = SYS_WINDOWS;

    template <typename T>
    struct conditional_os
    {
      conditional_os(const T& linux_var, const T& windows_var)
        : value{chooseValue(linux_var, windows_var)}
      {
      }

      T value;

    private:
      constexpr T chooseValue(const T& linux_var, const T& windows_var)
      {
        if constexpr (is_linux_v)
          return linux_var;
        else if constexpr (windows_var)
          return windows_var;
        throw std::runtime_error{"Unrecognized system"};
      }
    };
  } /* !meta */
} /* !lel */

#if 0
Usage example
static constexpr const char* a = conditional_os<const char*>{"linux", "windows"}.value;
#endif

#undef SYS_LINUX
#undef SYS_WINDOWS
