#pragma once

#include "IS.hh"
#include "IEListener.hh"
#include "dlloader/OSLoader.hpp"
#include "log/Log.hh"
#include <experimental/filesystem>
#include <memory>
#include <list>

struct SystemData
{
  std::experimental::filesystem::path path;
  lel::OSLoader loader;
  std::shared_ptr<IS> sys;
};

class Core : public IEListener, public std::enable_shared_from_this<Core>
{
public:
  using SysPtr = std::shared_ptr<IS>;

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
  bool _quit;
  std::list<SystemData> _data;
  std::list<std::string> _addRequest;
  std::list<std::string> _remRequest;

public:
  static std::string_view sysLibPath;
  static std::string_view autoLoadedSysRegex;
  static lel::Log log;
};
