#pragma once

#include "E/CRTPE.hpp"
#include "E/CManagerEvent/cmanagerevent_export.h"
#include "Utility/Fwd.hh"
#include "C/IDComponent.hh"
#include <variant>

namespace lel::ecs::event
{
  class CMANAGEREVENT_EXPORT CManagerEvent : public CRTPE<CManagerEvent>
  {
  public:
    using CPtr = std::shared_ptr<component::IC>;
    using CID = component::IDComponent;
    using Data = std::variant<CPtr, CID>;

  public:
    enum class Type : char
    {
      // EVENT
      COMP_CREATED,

      // OK
      COMP_ADDED,

      // ERROR
      COMP_ALREADY_ADDED,
      COMP_DTOR_NOT_FOUND,
    };

  public:
    CManagerEvent(const Type t);
    template <typename T>
    CManagerEvent(const Type t, const T& data)
      : _t{t}
      , _data{data}
    {}
    ~CManagerEvent() override = default;

    Type getType() const;
    Data getData() const;

  private:
    Type _t;
    Data _data;
  };
} /* !lel::ecs::event */
