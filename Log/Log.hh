#pragma once

#include <iostream>

// _DEBUG for Debug mode macro of MSVC
#if DEBUG || _DEBUG
# define DEBUG_VALUE true
#else
# define DEBUG_VALUE false
#endif /* !DEBUG */

namespace lel
{
  namespace details
  {
    struct has_debug
    {
      static const constexpr bool value = DEBUG_VALUE;
    };

    const bool has_debug_v = has_debug::value;
  } /* !details */
} /* !lel */

#undef DEBUG_VALUE

namespace lel
{
  class Log
  {
  public:
    Log(std::ostream& = std::cout);
    void setStream(std::ostream&);

    template <typename T>
    Log& operator<<(const T& t)
    {
      if constexpr (details::has_debug_v)
        *_stream << t;
      return *this;
    }

  private:
    std::ostream* _stream = &std::cout;
  };
} /* !lel */
