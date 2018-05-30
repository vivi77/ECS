#pragma once

#include <unordered_map>

namespace lel::ecs::utility
{
  template <class ID>
  class IDCenter
  {
    using Key = std::size_t;

  public:
    void bindID(const std::string& path, const ID& id)
    {
      _ids.emplace(std::hash<std::string>{}(path), id);
    }

    template <class C>
    void bindID(const ID& id)
    {
      _ids.emplace(typeid(C).hash_code(), id);
    }

    template <class C>
    ID getID() const
    {
      const auto key = typeid(C).hash_code();
      const auto it = _ids.find(key);
      return it != std::end(_ids) ? it->second : ID{};
    }

    ID getID(const std::string& path) const
    {
      const auto key = std::hash<std::string>{}(path);
      const auto it = _ids.find(key);
      // ID{} should return an invalid id
      return it != std::end(_ids) ? it->second : ID{};
    }

  private:
    std::unordered_map<Key, ID> _ids;
  };
} /* !lel::ecs::utility */
