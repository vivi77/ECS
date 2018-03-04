#pragma once

#include "IS.hh"
#include "IEListener.hh"
#include "dlloader/OSLoader.hpp"
#include "log/Log.hh"
#include <memory>
#include <vector>

class Core : public IEListener, public std::enable_shared_from_this<Core>
{
  using SysPtr = std::shared_ptr<IS>;

public:
  Core();
  virtual ~Core() = default;
  void run();
  void update(const IEListener::EPtr&) override;

private:
  bool shouldQuit() const;
  void stopCore();

private:
  bool _quit;
  std::vector<lel::OSLoader> _sysLibs;
  std::vector<SysPtr> _systems;

// static
private:
  static std::vector<lel::OSLoader> searchLibraries();
  static std::vector<SysPtr> extractSystems(std::vector<lel::OSLoader>&);

private:
  static std::string_view sysLibPath;
  static std::string_view autoLoadedSysRegex;
  static lel::Log log;
};
