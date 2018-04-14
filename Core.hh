#pragma once

#include "E/IEListener.hh"
#include "E/EManager/EManager.hh"
#include "CoreSystemData.hh"
#include "Entity/EntityManager.hh"
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
    void update(const IEListener::EPtr&) override;

  private:
    bool shouldQuit() const;
    void stopCore();
    void delayedEventUpdate();
    bool trySystemRegistering(lel::ecs::CoreSystemData&);
    std::list<CoreSystemData> setupData();
    void updateAddRequest(std::list<std::string>&, std::list<CoreSystemData>&);
    void updateRemoveRequest(std::list<std::string>&, std::list<CoreSystemData>&);
    void reverseClear(std::list<CoreSystemData>&);

  private:
    bool _quit = false;
    entity::EntityManager _entityManager;
    event::EManager _eventManager;
    std::list<std::string> _addRequest;
    std::list<std::string> _remRequest;
    std::list<CoreSystemData> _data;

  public:
    static std::string_view sysLibPath;
    static std::string_view autoLoadedSysRegex;
  };
} /* !lel */
