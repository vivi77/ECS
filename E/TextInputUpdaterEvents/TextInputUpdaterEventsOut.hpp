#pragma once

#include "E/CRTPE.hpp"

namespace lel::ecs::event
{
  template <typename ID>
  class TextInputUpdaterEventsOut : public CRTPE<TextInputUpdaterEventsOut<ID>>
  {
  public:
    TextInputUpdaterEventsOut(const std::string& input)
      : _input{input}
    {}

    ~TextInputUpdaterEventsOut() override = default;

    std::string getInput() const
    {
      return _input;
    }

  private:
    std::string _input;
  };
} /* !lel::ecs::event */
