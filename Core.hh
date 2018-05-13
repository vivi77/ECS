#pragma once

#include "CoreSystemData.hh"
#include "E/IEListener.hh"
#include "E/EManager/EManager.hh"
#include "Entity/EntityManager.hh"
#include "S/CoreProxy/CoreProxy.hh"
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
    virtual ~Core() = default;
    void run();
    void addSystem(const std::string&);

    void update(const IEListener::EPtr&) override;

  private:
    bool shouldQuit() const;
    void stopCore();
    void delayedEventUpdate();
    bool trySystemRegistering(CoreSystemData&);
    void setupData();
    void updateAddRequest(std::list<CoreSystemData>&);
    void updateRemoveRequest(std::list<CoreSystemData>&);
    void reverseClear(std::list<CoreSystemData>&);

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
