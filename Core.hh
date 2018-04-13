#pragma once

#include "E/IEListener.hh"
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
    bool trySystemRegistering(lel::ecs::CoreSystemData& data);
    std::list<CoreSystemData> setupData();
    void updateAddRequest(std::list<std::string>& addRequest, std::list<CoreSystemData>& datalist);

  private:
    bool _quit = false;
    entity::EntityManager _entityManager;
    std::list<std::string> _addRequest;
    std::list<std::string> _remRequest;
    std::list<CoreSystemData> _data;

  public:
    static std::string_view sysLibPath;
    static std::string_view autoLoadedSysRegex;
  };
} /* !lel */
