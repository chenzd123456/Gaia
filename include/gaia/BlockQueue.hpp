#ifndef __GAIA_BLOCKQUEUE_H__
#define __GAIA_BLOCKQUEUE_H__

#include <stdint.h>

#include <condition_variable>
#include <mutex>
#include <queue>

namespace gaia {

template <typename T>
class BlockQueue {
 private:
  uint32_t m_max_size;
  std::condition_variable m_not_empty_cv;
  std::condition_variable m_not_full_cv;
  std::mutex m_mutex;
  std::queue<T> m_queue;

 public:
  BlockQueue() : m_max_size(0) {}

  uint32_t Size() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.size();
  }

  uint32_t MaxSize() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_max_size;
  }

  void MaxSize(uint32_t max_size) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_max_size = max_size;
  }

  void Push(T item) {
    std::unique_lock<std::mutex> lock(m_mutex);
    const auto is_not_full = [&] {
      return m_max_size == 0 || m_max_size > m_queue.size();
    };
    m_not_full_cv.wait(lock, is_not_full);
    m_queue.push(item);
    lock.unlock();
    m_not_empty_cv.notify_one();
  }

  T Pop() {
    std::unique_lock<std::mutex> lock(m_mutex);
    const auto is_not_empty = [&] { return !m_queue.empty(); };
    m_not_empty_cv.wait(lock, is_not_empty);
    auto item = m_queue.front();
    m_queue.pop();
    lock.unlock();
    m_not_full_cv.notify_one();
    return item;
  }
};
}  // namespace gaia

#endif  // __GAIA_BLOCKQUEUE_H__