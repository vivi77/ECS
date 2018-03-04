#pragma once

#include "IS.hh"

template <class D>
class CRTPS : public IS
{
  using ID = typename IS::ID;

public:
  virtual ~CRTPS() = default;

  static void assignID(const ID id)
  {
    if (!isIDAssigned())
    {
      _id = id;
      _idAssigned = true;
    }
  }

  ID getID() const final
  {
    return getSystemID();
  }

  static ID getSystemID()
  {
    return _id;
  }

  static bool isIDAssigned()
  {
    return _idAssigned;
  }

private:
  static ID _id;
  static bool _idAssigned;
};

template <class D>
typename CRTPS<D>::ID CRTPS<D>::_id = 0;

template <class D>
bool CRTPS<D>::_idAssigned = false;
