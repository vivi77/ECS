#pragma once

#include "CRTPS.hpp"
#include "IEListener.hh"
#include "Log.hh"
#include <fstream>

namespace lel
{
  namespace ecs
  {
    namespace system
    {
      class Debug : public CRTPS<Debug>, public event::IEListener
      {
      public:
        Debug();
        virtual ~Debug() = default;
        void exec() override;
        void update(const EPtr&) override;
        void registerEntity(const EntityPtr&) override;
        void setup() override;
        void atRemove() override;

      private:
        std::ofstream _logFile;
        lel::Log _log;
      };
    } /* !system */
  } /* !ecs */
} /* !lel */
