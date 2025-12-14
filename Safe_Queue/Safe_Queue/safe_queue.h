#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <utility>

// Потокобезопасная очередь
template <typename T>
class safe_queue {
public:
    safe_queue() = default;
    safe_queue(const safe_queue&) = delete;
    safe_queue& operator=(const safe_queue&) = delete;

    // Добавить элемент в очередь
    void push(T value) {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push(std::move(value));
        }
        m_cond.notify_one();
    }

    // Блокирующее извлечение элемента.
    // Ожидает, пока очередь не станет непустой.
    T pop() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [this] { return !m_queue.empty(); });

        T value = std::move(m_queue.front());
        m_queue.pop();
        return value;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

private:
    mutable std::mutex m_mutex;
    std::condition_variable m_cond;
    std::queue<T> m_queue;
};

