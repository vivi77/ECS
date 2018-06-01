#pragma once

#include "IS.hh"
#include "Utility/TemplateUniqueID.hpp"

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
