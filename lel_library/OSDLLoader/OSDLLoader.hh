#pragma once

#ifdef __linux__
# include "LinuxDLLoader.hh"

namespace lel
{
  using OSDLLoader = lel::LinuxDLLoader;
} /* !lel */
#elif _WIN32
# include "WindowsDLLoader.hh"

namespace lel
{
  using OSDLLoader = WindowsDLLoader;
} /* !lel */
#endif
