#include "Log.hh"

namespace lel
{
  Log::Log(std::ostream& stream)
    : _stream{&stream}
  {
    if constexpr (details::has_debug_v)
      std::cout << "LOG ACTIVATED\n";
    else
      std::cout << "LOG DEACTIVATED\n";
  }

  void Log::setStream(std::ostream& stream)
  {
    if constexpr (details::has_debug_v)
      _stream = &stream;
  }
} /* !lel */
