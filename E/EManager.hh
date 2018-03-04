#pragma once

#include "emanager_export.h"
#include "IEListener.hh"
#include <vector>

class IS;

class EMANAGER_EXPORT EManager
{
public:
  using IEListenerPtr = std::shared_ptr<IEListener>;
  using SPtr = std::shared_ptr<IS>;

public:
  static void fire(const IEListener::EPtr& e);
  static void registerListener(const IEListenerPtr& listener);
  static void deregisterListener(const IEListenerPtr& listener);
  static void registerListenerSystem(const SPtr& s);
  static void deregisterListenerSystem(const SPtr& s);

private:
  static IEListenerPtr castSystemToListener(const SPtr& s);

private:
  static std::vector<IEListenerPtr> _listeners;
};
