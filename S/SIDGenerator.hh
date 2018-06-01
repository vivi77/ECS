#pragma once

#include "IDSystem.hh"
#include "Utility/IIDGenerator.hpp"

namespace lel::ecs::system
{
  class SIDGenerator : public utility::IIDGenerator<IDSystem>
  {
  public:
    IDSystem generateID();

  private:
    IDSystem _id{0};
  };
} /* !lel::ecs::system */
