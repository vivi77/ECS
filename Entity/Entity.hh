#pragma once

#include "C/IC.hh"
#include "Entity/entitylogic_export.h"
#include <vector>
#include <memory>

class ENTITYLOGIC_EXPORT Entity
{
public:
  using CPtr = std::shared_ptr<IC>;
  using CContainer = std::vector<CPtr>;

public:
  using ID = unsigned;

public:
  Entity(const ID, std::initializer_list<CPtr>);

  ID getID() const;
  CContainer getComponents() const;

  void addComponent(const CPtr& comp);
  void removeComponent(const IC::ID);

private:
  ID _id;
  CContainer _components;
};
