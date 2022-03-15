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

  uint32_t MaxTaskCount() { return m_queue.MaxSize(); }

  void MaxTaskCount(uint32_t max_count) { m_queue.MaxSize(max_count); }

  uint32_t TaskCount() { return m_queue.Size(); }

  void AddTask(std::function<void()> task) { m_queue.Push(task); }

  std::function<void()> RemoveTask() { return m_queue.Pop(); }

  void Stop() {
    AddTask([]() { throw ReactThreadStop(); });
  }

  void Join() { m_thread.join(); }

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
          // TODO
        }
      }
    });
  }
};
}  // namespace gaia

#endif  // __GAIA_REACTTHREAD_H__