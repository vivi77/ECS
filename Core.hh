#pragma once

#include "CoreSystemData.hh"
#include "IEListener.hh"
#include "EManager.hh"
#include "EntityManager.hh"
#include "CoreProxy.hh"
#include <memory>
#include <list>

namespace lel::ecs
{
  class Core : public event::IEListener, public std::enable_shared_from_this<Core>
  {
  public:
    using SysPtr = std::shared_ptr<system::IS>;

  public:
    Core();
    ~Core() override = default;
    void run();

    void update(const IEListener::EPtr&) override;

  private:
    bool shouldQuit() const;
    void stopCore();
    void delayedEventUpdate();
    bool trySystemRegistering(CoreSystemData&);
    void setupData();
    void updateAddRequest();
    void updateRemoveRequest();
    void updateReloadRequest();
    void reverseClear(std::list<CoreSystemData>&);
    void addSystem(const std::string& sysPath);
    void removeSystem(const std::string& sysPath);

  private:
    bool _quit = false;
    entity::EntityManager _entityManager;
    event::EManager _eventManager;
    std::list<CoreSystemData> _data;
    std::list<CoreProxy> _proxies;

  public:
    static std::string_view sysLibPath;
    static std::string_view autoLoadedSysRegex;
  };
} /* !lel */
