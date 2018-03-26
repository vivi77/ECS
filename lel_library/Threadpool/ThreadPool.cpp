#include "ThreadPool.hh"

namespace lel
{
  ThreadPool::ThreadPool(unsigned nbWorker)
  {
    while (nbWorker != 0)
    {
      _workers.emplace_back([this]() { threadRoutine(); });
      --nbWorker;
    }
  }

  ThreadPool::~ThreadPool()
  {
    shutdown();
    for (auto& wo : _workers)
    {
      if (wo.joinable())
        wo.join();
    }
  }

  void ThreadPool::addOrder(const Callable& order)
  {
    _orders.push(order);
    _condVar.notify_one();
  }

  void ThreadPool::shutdown()
  {
    _shutdown = true;
    _condVar.notify_all();
  }

  void ThreadPool::threadRoutine()
  {
    while (!_shutdown)
    {
      {
        std::unique_lock<decltype(_mutex)> lock{_mutex};
        _condVar.wait(lock, [this]() { return !_orders.isEmpty() || _shutdown; });
      }
      if (!_shutdown)
        _orders.pop()();
    }
  }
} /* !lel */
