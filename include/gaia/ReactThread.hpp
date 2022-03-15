#ifndef __GAIA_REACTTHREAD_H__
#define __GAIA_REACTTHREAD_H__

#include <exception>
#include <functional>
#include <thread>

#include "BlockQueue.hpp"

namespace gaia {

/**
 * @brief 可复用的线程。
 * 内部维护一个任务队列，可以设置任务队列的最大任务数
 */
class ReactThread {
 private:
  /**
   * @brief 用于终止线程
   * 当线程内抛出 ReactThreadStop 异常，线程终止。
   */
  class ReactThreadStop : public std::exception {};

 private:
  BlockQueue<std::function<void()>> m_queue;
  std::thread m_thread;

 public:
  /**
   * @brief Construct a new React Thread object
   *
   */
  ReactThread() { _Init(); };

  /**
   * @brief 查看任务队列的最大任务数。
   *
   * @return uint32_t
   */
  uint32_t MaxTaskCount() { return m_queue.MaxSize(); }

  /**
   * @brief 设置任务队列的最大任务数。
   *
   * @param max_count 任务队列的最大任务数
   */
  void MaxTaskCount(uint32_t max_count) { m_queue.MaxSize(max_count); }

  /**
   * @brief 当前任务队列中的任务个数
   *
   * @return uint32_t
   */
  uint32_t TaskCount() { return m_queue.Size(); }

  /**
   * @brief 向任务队列中添加任务
   *
   * @param task 可执行的任务，可以是函数、函数对象、仿函数 或 Lambda
   */
  void AddTask(std::function<void()> task) { m_queue.Push(task); }

  /**
   * @brief 终止线程。
   * 调用 Stop() 后，会继续执行任务，直到将调用 Stop() 方法前添加的任务执行完。
   * 调用 Stop() 后，请使用 Join() 函数等待线程终止。
   */
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