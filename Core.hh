#pragma once

#include "IEListener.hh"
#include "CoreSystemData.hh"
#include <memory>
#include <list>

namespace lel
{
  namespace ecs
  {
    class Core : public event::IEListener, public std::enable_shared_from_this<Core>
    {
    public:
      using SysPtr = std::shared_ptr<lel::ecs::system::IS>;

    public:
      Core();
      virtual ~Core() = default;
      void run();
      void update(const IEListener::EPtr&) override;

    private:
      bool shouldQuit() const;
      void stopCore();
      void delayedEventUpdate();

    private:
      bool _quit = false;
      std::list<CoreSystemData> _data;
      std::list<std::string> _addRequest;
      std::list<std::string> _remRequest;

    public:
      static std::string_view sysLibPath;
      static std::string_view autoLoadedSysRegex;
    };
  } /* !ecs */
} /* !lel */
