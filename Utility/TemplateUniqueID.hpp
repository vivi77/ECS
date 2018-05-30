#pragma once

#include "IIDGenerator.hpp"
#include "Utility/Fwd.hh"
#include <functional>

namespace lel::ecs::meta
{
  namespace details
  {
    template <class C>
    struct void_in;
    template <template <typename> class Out, typename In>
    struct void_in<Out<In>>
    {
      using type = Out<void>;
    };
    template <class C>
    using void_in_t = typename void_in<C>::type;


    template <class C, typename ID>
    class TemplateUniqueID_helper;
    template <template <typename> class Out, typename ID>
    class TemplateUniqueID_helper<Out<void>, ID>
    {
    public:
      // TODO: Try to make callback a template parameter ?
      static ID generateID(const std::function<void(ID)>& callback = nullptr)
      {
        if (_generator == nullptr)
          _generator = ::createGenerator<ID>();
        auto newID = _generator->generateID();
        if (callback)
          callback(newID);
        return newID;
      }

    private:
      static std::unique_ptr<utility::IIDGenerator<ID>> _generator;
    };

    template <template <typename> class Out, typename ID>
    std::unique_ptr<utility::IIDGenerator<ID>> TemplateUniqueID_helper<Out<void>, ID>::_generator = nullptr;
  } /* !details */

  // It provides a way to generate unique ID to each template class of a
  // class template
  // We void the template argument of the class <C> in order to only care about
  // the class template that C use
  template <class C, typename ID>
  struct TemplateUniqueID : public details::TemplateUniqueID_helper<details::void_in_t<C>, ID>
  {
  };
} /* !lel::ecs::meta */
