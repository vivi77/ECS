#pragma once

#include <string_view>

namespace lel::ecs::system
{
  namespace details
  {
    inline constexpr std::string_view getFilename(std::string_view p)
    {
      auto idx = p.find_last_of('/');
      if (idx == std::string_view::npos)
        idx = 0;
      else
        ++idx;
      auto newP = p.substr(idx);

      idx = newP.find_first_of('.');
      return idx == std::string_view::npos ? newP : newP.substr(0, idx);
    }
  } /* !details */
} /* !lel::ecs::system */
#define FILE_NO_EXTENSION() getFilename(__FILE__)

#define ECS_CREATE_IDSYSTEM_FULL(system_name, class_name)\
namespace lel::ecs::system\
{\
  namespace details\
  {\
    using system_name##IDGenerator = meta::TemplateUniqueID<class_name, IS::ID>;\
  }\
  IDSystem g_systemID{details::system_name##IDGenerator::generateID()};\
}

#define ECS_CREATE_IDSYSTEM(system_name)\
  ECS_CREATE_IDSYSTEM_FULL(system_name, CRTPS<system_name>)
