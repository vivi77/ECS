#include "Debug.hh"
#include "E/CoreEvent/CoreEvent.hh"
#include "E/EManagerEvent/EManagerEvent.hh"
#include "E/CManagerEvent/CManagerEvent.hh"
#include "E/CLISystemEvent/CLISystemEvent.hh"
#include "E/EntityManagerEvent/EntityManagerEvent.hh"
#include "E/DebugEvent/DebugEvent.hh"
#include <sstream>

namespace
{
  inline void requestEvent(lel::Log& log, const std::string& msg)
  {
    log << "\033[34m[ RQ ] " << msg;
  }

  inline void badEvent(lel::Log& log, const std::string& msg)
  {
    log << "\033[31m[ KO ] " << msg;
  }

  inline void okEvent(lel::Log& log, const std::string& msg)
  {
    log << "\033[32m[ OK ] " << msg;
  }

  inline void warnEvent(lel::Log& log, const std::string& msg)
  {
    log << "\033[33m[WARN] " << msg;
  }

  inline void infoEvent(lel::Log& log, const std::string& msg)
  {
    log << "[INFO] " << msg;
  }

  std::string to_string(void* ptr)
  {
    std::stringstream ss;
    ss << ptr;
    return ss.str();
  }

  void debugEvent(const std::shared_ptr<lel::ecs::event::CoreEvent>& event, lel::Log& log)
  {
    using CoreEvent = lel::ecs::event::CoreEvent;

    switch (event->getType())
    {
      case CoreEvent::Type::ADD_SYSTEM:
        requestEvent(log, {"Add system '" + event->getData()[0] + "' requested"});
        break;
      case CoreEvent::Type::ADD_SYSTEM_FAILURE:
        badEvent(log, {"Cannot add system '" + event->getData()[0] + "'"});
        break;
      case CoreEvent::Type::ADD_SYSTEM_SUCCESS:
        okEvent(log, {"System '" + event->getData()[0] + "' (ID#"+
                event->getData()[2] + ") added to Core execution (" +
                event->getData()[1] + ")"});
        break;
      case CoreEvent::Type::ALREADY_ADDED_SYSTEM:
        warnEvent(log, {"System '" + event->getData()[0] + "' already added"});
        break;
      case CoreEvent::Type::CLOSING:
        infoEvent(log, "Program is closing. Wait for everything to be removed");
        break;
      case CoreEvent::Type::EXIT:
        requestEvent(log, "Closing program requested");
        break;
      case CoreEvent::Type::INVALID_SYSTEM:
        badEvent(log, {"System from library '" + event->getData()[0]
                 + "' is not valid" + "\033[1;31m\nReason: " + event->getData()[1]});
        break;
      case CoreEvent::Type::REM_SYSTEM:
        requestEvent(log, "Remove system '" + event->getData()[0] + "' requested");
        break;
      case CoreEvent::Type::REM_SYSTEM_FAILURE:
        badEvent(log, {"Cannot remove system '" + event->getData()[0] + "'"});
        break;
      case CoreEvent::Type::REM_SYSTEM_SUCCESS:
        okEvent(log, {"System '" + event->getData()[0] + "' (ID#" +
                event->getData()[2] + ") removed to Core execution (" +
                event->getData()[1] + ")"});
        break;
      case CoreEvent::Type::SYSTEM_NOT_FOUND:
        badEvent(log, {"System '" + event->getData()[0] + "' not found"});
        break;
      default:
        infoEvent(log, "Unknown component event");
        break;
    }
  }

  void debugEvent(const std::shared_ptr<lel::ecs::event::EManagerEvent>& event, lel::Log& log)
  {
    using EManagerEvent = lel::ecs::event::EManagerEvent;
    switch (event->getType())
    {
      case EManagerEvent::Type::EVENT_ADDED:
        {
          std::string msg = "Add event ID#";
          msg += std::to_string(std::get<EManagerEvent::ID>(event->getData()));
          msg += " requested";
          okEvent(log, msg);
          break;
        }
      case EManagerEvent::Type::EVENT_ALREADY_ADDED:
        badEvent(log, "Event ID#" + std::to_string(std::get<EManagerEvent::ID>(event->getData())) + " already added");
        break;
      case EManagerEvent::Type::LISTENER_ADDED:
        okEvent(log, "Listener added (" + std::get<std::string>(event->getData()) + ")");
        break;
      case EManagerEvent::Type::LISTENER_ALREADY_ADDED:
        badEvent(log, "Listener already added (" + std::get<std::string>(event->getData()) + ")");
        break;
      case EManagerEvent::Type::LISTENER_NOT_FOUND:
        badEvent(log, "Listener not found (" + std::get<std::string>(event->getData()) + ")");
        break;
      case EManagerEvent::Type::LISTENER_REMOVED:
        okEvent(log, "Listener removed (" + std::get<std::string>(event->getData()) + ")");
        break;
      case EManagerEvent::Type::NOT_LISTENER:
        badEvent(log, "Object at address " + std::get<std::string>(event->getData()) + "is not a listener");
        break;
      case EManagerEvent::Type::EVENT_DTOR_NOT_FOUND:
        badEvent(log, "Event ID#" + std::to_string(std::get<EManagerEvent::ID>(event->getData())) + " has not registered a dtor. Creation of event FORBIDDEN");
        break;
      default:
        infoEvent(log, "Unknown component event");
        break;
    }
  }

  void debugEvent(const std::shared_ptr<lel::ecs::event::CManagerEvent>& event, lel::Log& log)
  {
    using CManagerEvent = lel::ecs::event::CManagerEvent;

    switch (event->getType())
    {
      case CManagerEvent::Type::COMP_ADDED:
        okEvent(log, "Component ID#" + std::to_string(std::get<CManagerEvent::CID>(event->getData())) + " added");
        break;
      case CManagerEvent::Type::COMP_ALREADY_ADDED:
        badEvent(log, "Component ID#" + std::to_string(std::get<CManagerEvent::CID>(event->getData())) + " already added");
        break;
      case CManagerEvent::Type::COMP_CREATED:
        okEvent(log, "Component created (address:" + to_string(std::get<CManagerEvent::CPtr>(event->getData()).get()) + ")");
        break;
      case CManagerEvent::Type::COMP_DTOR_NOT_FOUND:
        badEvent(log, "Component ID#" + std::to_string(std::get<CManagerEvent::CID>(event->getData())) + " not found");
        break;
      default:
        infoEvent(log, "Unknown component event");
        break;
    }
  }

  void debugEvent(const std::shared_ptr<lel::ecs::event::CLISystemEvent>& event, lel::Log& log)
  {
    using CLISystemEvent = lel::ecs::event::CLISystemEvent;

    switch (event->getType())
    {
      case CLISystemEvent::Type::DISABLE:
        requestEvent(log, "Request CLISystem to be disabled. There will be no confirmation response");
        break;
      case CLISystemEvent::Type::ENABLE:
        requestEvent(log, "Request CLISystem to be enabled. There will be no confirmation response");
        break;
      default:
        infoEvent(log, "Unknown component event");
        break;
    }
  }

  void debugEvent(const std::shared_ptr<lel::ecs::event::EntityManagerEvent>& event, lel::Log& log)
  {
    using EntityManagerEvent = lel::ecs::event::EntityManagerEvent;

    switch (event->getType())
    {
      case EntityManagerEvent::Type::ENTITY_CREATED:
        okEvent(log, "Entity CREATED with ID#" + std::to_string(event->getEntityID()));
        break;
      case EntityManagerEvent::Type::ENTITY_DESTROYED:
        okEvent(log, "Entity DESTROYED with ID#" + std::to_string(event->getEntityID()));
        break;
      case EntityManagerEvent::Type::ENTITY_NOT_FOUND:
        badEvent(log, "Entity ID#" + std::to_string(event->getEntityID()) + " not found");
        break;
      default:
        infoEvent(log, "Unknown component event");
        break;
    }
  }

  void debugEvent(const std::shared_ptr<lel::ecs::event::DebugEvent>& e, lel::Log& log)
  {
    infoEvent(log, e->getMessage());
  }

  [[maybe_unused]]
  void debugEventFallback(const lel::ecs::system::Debug::EPtr& event, lel::Log& log)
  {
    log << "Unknwon event with ID#" << event->getID() << " fired";
  }

  template <class C, typename ... Args>
  struct exist_debugEventFct
  {
    struct No {};
    struct Yes {};

    template <class LHS, typename ... A, typename = decltype(debugEvent(std::declval<A>()...))>
      static Yes helper(int);
    template <typename, typename ...>
      static No helper(...);

    static constexpr bool value = std::is_same_v<decltype(helper<C, Args...>(0)), Yes>;
  };

  template <typename T>
  struct updateCtor;

  template <typename T>
  struct updateCtor<std::tuple<T>>
  {
    inline static void partialDebugEvent(const lel::ecs::system::Debug::EPtr& event, lel::Log& log)
    {
      if (event->getID() == T::getEventID())
      {
        using HeadPtr = const decltype(std::static_pointer_cast<T>(event));
        if constexpr (exist_debugEventFct<T, HeadPtr&, lel::Log&>::value)
          debugEvent(std::static_pointer_cast<T>(event), log);
        else
          debugEventFallback(event, log);
      }
      else
        log << "Event with an unknown id: " << event->getID();
    }
  };

  template <typename Head, typename ... Tail>
  struct updateCtor<std::tuple<Head, Tail...>>
  {
    inline static void partialDebugEvent(const lel::ecs::system::Debug::EPtr& event, lel::Log& log)
    {
      if (event->getID() == Head::getEventID())
      {
        using HeadPtr = const decltype(std::static_pointer_cast<Head>(event));
        if constexpr (exist_debugEventFct<Head, HeadPtr&, lel::Log&>::value)
          debugEvent(std::static_pointer_cast<Head>(event), log);
        else
          debugEventFallback(event, log);
      }
      else
        updateCtor<std::tuple<Tail...>>::partialDebugEvent(event, log);
    }
  };
} /* ! */

namespace lel::ecs::system
{
  Debug::Debug()
    : _logFile{"debug_ecs.log"}
    , _log{_logFile}
  {
    // Fallback in case of error
    if (!_logFile)
      _log.setStream(std::cout);
  }

  void Debug::exec()
  {
  }

  void Debug::update(const EPtr& event)
  {
    using namespace lel::ecs::event;

    using TypeList = std::tuple<CoreEvent, EManagerEvent, CManagerEvent,
          CLISystemEvent, EntityManagerEvent, DebugEvent>;

    updateCtor<TypeList>::partialDebugEvent(event, _log);
    _log << "\033[0m\n";
  }

  void Debug::registerEntity(const EntityPtr&)
  {}

  void Debug::setup()
  {}

  void Debug::atRemove()
  {
    okEvent(_log, "DebugSystem unloaded (" + to_string(this) + ")\n");
  }
} /* !lel::ecs::system */
