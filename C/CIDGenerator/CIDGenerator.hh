#pragma once

#include "C/CIDGenerator/cidgen_export.h"
#include "Utility/Fwd.hh"
#include "Utility/IIDGenerator.hpp"

namespace lel::ecs::component
{
  class CIDGEN_EXPORT CIDGenerator : public utility::IIDGenerator<IDComponent>
  {
  public:
    using ID = IDComponent;

  public:
    ID generateID() override;

  private:
    ID _id;
  };

  namespace old
  {
    class CIDGEN_EXPORT CIDGenerator
    {
      using ID = unsigned;

    public:
      static CIDGenerator& getSingleton();
      ID generateID();

    private:
      CIDGenerator();

    private:
      ID _idGenerator;
    };
  } /* !old */
} /* !lel::ecs::component */
