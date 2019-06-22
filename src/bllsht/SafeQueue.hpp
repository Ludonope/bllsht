#ifndef BLLSHT_BLLSHT_SAFEQUEUE_HPP
#define BLLSHT_BLLSHT_SAFEQUEUE_HPP

#include <mutex>
#include <queue>

namespace bllsht {
template <class T> class SafeQueue {
public:
  template <class... Args> decltype(auto) emplace(Args &&... args) {
    m_queue.emplace(std::forward<Args>(args)...);
  }

  void push(T const &value) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_queue.push(value);
  }

  void push(T &&value) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_queue.push(std::move(value));
  }

  bool pop(T &value) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_queue.empty()) {
      return false;
    }
    value = m_queue.back();
    m_queue.pop();
    return true;
  }

private:
  std::queue<T> m_queue;
  std::mutex m_mutex;
};
} // namespace bllsht

#endif // BLLSHT_BLLSHT_SAFEQUEUE_HPP