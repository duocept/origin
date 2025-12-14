#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <future>
#include <type_traits>
#include <stdexcept>
#include <utility>

#include "safe_queue.h"

// Пул потоков на базе потокобезопасной очереди
class thread_pool {
public:
    thread_pool()
        : m_stopping(false)
    {
        unsigned int thread_count = std::thread::hardware_concurrency();
        if (thread_count == 0) {
            thread_count = 2; // на случай, если hardware_concurrency() вернул 0
        }

        m_threads.reserve(thread_count);
        for (unsigned int i = 0; i < thread_count; ++i) {
            m_threads.emplace_back(&thread_pool::work, this);
        }
    }

    ~thread_pool() {
        // Сигнализируем, что новых задач больше не будет
        m_stopping.store(true);

        // Кладём в очередь по "пустой" задаче на каждый поток — это сигналы завершения
        for (std::size_t i = 0; i < m_threads.size(); ++i) {
            m_tasks.push(std::function<void()>()); // пустая std::function => признак "выход"
        }

        // Дожидаемся завершения всех потоков
        for (auto& t : m_threads) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    // submit: кладёт задачу в очередь и возвращает future результата
    template <class F, class... Args>
    auto submit(F&& f, Args&&... args)
        -> std::future<typename std::invoke_result<F, Args...>::type>
    {
        using return_type = typename std::invoke_result<F, Args...>::type;

        if (m_stopping.load()) {
            throw std::runtime_error("thread_pool уже завершает работу, submit невозможен");
        }

        // Заворачиваем функцию и аргументы в packaged_task
        auto task_ptr = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task_ptr->get_future();

        // Кладём в очередь std::function<void()>, которая вызовет packaged_task
        m_tasks.push([task_ptr]() {
            (*task_ptr)();
            });

        return res;
    }

private:
    // Рабочий метод, который выполняется в потоках пула
    void work() {
        while (true) {
            std::function<void()> task = m_tasks.pop();

            // Пустая задача — сигнал завершить поток
            if (!task) {
                break;
            }

            // Выполняем задачу
            task();
        }
    }

    std::vector<std::thread> m_threads;
    safe_queue<std::function<void()>> m_tasks;
    std::atomic<bool> m_stopping;
};

