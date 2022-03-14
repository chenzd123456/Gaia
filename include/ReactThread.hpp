#ifndef __GAIA_REACTTHREAD_H__
#define __GAIA_REACTTHREAD_H__

#include <exception>
#include <functional>
#include <thread>

#include "BlockQueue.hpp"

namespace gaia {
class ReactThread {
 private:
  class ReactThreadStop : public std::exception {};

  BlockQueue<std::function<void()>> m_queue;
  std::thread m_thread;

 public:
  ReactThread() { _Init(); };

  void AddTask(std::function<void()> task) { m_queue.Push(task); }

  void Stop() {
    AddTask([]() { throw ReactThreadStop(); });
  }

 private:
  void _Init() {
    m_thread = std::thread([&]() {
      while (true) {
        auto task = m_queue.Pop();

        try {
          task();
        } catch (const ReactThreadStop& e) {
          break;
        } catch (const std::exception& e) {
        }
      }
    });
  }
};
}  // namespace gaia

#endif  // __GAIA_REACTTHREAD_H__