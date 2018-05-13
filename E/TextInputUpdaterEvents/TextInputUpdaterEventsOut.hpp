#pragma once

#include "E/CRTPE.hpp"

namespace lel::ecs::event
{
  template <class CompID>
  class TextInputUpdaterEventsOut : public CRTPE<TextInputUpdaterEventsOut<CompID>>
  {
  public:
    TextInputUpdaterEventsOut(const CompID& id, const std::string& input)
      : _id{id}
      , _input{input}
    {}

    ~TextInputUpdaterEventsOut() override = default;

    CompID getSenderID() const
    {
      return _id;
    }

    std::string getInput() const
    {
      return _input;
    }

  private:
    CompID _id;
    std::string _input;
  };
} /* !lel::ecs::event */
