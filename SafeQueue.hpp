#pragma once

#include <deque>
#include <mutex>

namespace lel
{
  /** @brief Simple thread-safe queue
   */
  template <typename T>
  class SafeQueue
  {
  public:
    void push(const T& item)
    {
      std::lock_guard<decltype(_mutex)> lock{_mutex};
      _container.emplace_back(item);
    }

    T pop()
    {
      std::lock_guard<decltype(_mutex)> lock{_mutex};
      T item = _container.front();
      _container.pop_front();
      return item;
    }

    bool isEmpty() const
    {
      std::lock_guard<decltype(_mutex)> lock{_mutex};
      return _container.empty();
    }

  private:
    std::deque<T> _container;
    mutable std::mutex _mutex; //is mutable because 'isEmpty' should be 'const' but mutex should be usable there
  };
} /* !lel */
