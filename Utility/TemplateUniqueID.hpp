#pragma once

#include "IIDGenerator.hpp"
#include "Utility/Fwd.hh"

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
      static ID generateID()
      {
        if (_generator == nullptr)
          _generator = ::createGenerator<ID>();
        return _generator->generateID();
      }

    private:
      // Users of this class has to instantiate their own generator
      // TODO: Has a default generator ?
      static std::unique_ptr<utility::IIDGenerator<ID>> _generator;
    };

    template <template <typename> class Out, typename ID>
    std::unique_ptr<utility::IIDGenerator<ID>> TemplateUniqueID_helper<Out<void>, ID>::_generator = nullptr;
  } /* !details */

  template <class C, typename ID>
  struct TemplateUniqueID : public details::TemplateUniqueID_helper<details::void_in_t<C>, ID>
  {
  };
} /* !lel::ecs::meta */
