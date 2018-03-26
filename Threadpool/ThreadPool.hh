#pragma once

#include "SafeQueue.hpp"
#include <thread>
#include <functional>
#include <condition_variable>

namespace lel
{
  class ThreadPool
  {
  public:
    using Callable = std::function<void()>;
    using Worker = std::thread;

  public:
    ThreadPool(unsigned nbWorker);
    ~ThreadPool();
    void addOrder(const Callable& order);
    void shutdown();

  private:
    void threadRoutine();

  private:
    std::vector<Worker> _workers;
    SafeQueue<Callable> _orders;
    std::mutex _mutex;
    std::condition_variable _condVar;
    bool _shutdown = false;
  };
} /* !lel */
