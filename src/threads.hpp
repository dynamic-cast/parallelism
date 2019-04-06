#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

namespace Threads {

template <typename Task, typename Func>
struct ThreadPool {
    // ctors
    ThreadPool(unsigned int _max_pool_size, std::vector<Task> tasks,
               Func operation)
        : max_pool_size(_max_pool_size), queue(std::move(tasks)) {
        std::vector<std::thread> threads;
        for (unsigned int i = 0; i < max_pool_size; i++) {
            std::thread t(&ThreadPool::image_work, this, operation);
            threads.emplace_back(std::move(t));
        }

        while (!queue.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        shutdown = true;

        for (auto &thread : threads) {
            thread.join();
        }
    }
    // explicitly disallow copy and move
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;

    void addTask(const Task &task) {
        std::lock_guard<std::mutex> lock(pool_mutex);
        queue.push_back(task);
    }

  private:
    unsigned int max_pool_size;
    std::vector<Task> queue;
    bool shutdown = false;
    std::mutex pool_mutex;

    void image_work(Func operation) {
        while (!shutdown) {
            Task task;
            bool has_task = false;
            if (!queue.empty()) {
                std::lock_guard<std::mutex> lock(pool_mutex);
                if (!queue.empty()) {
                    task = queue.back();
                    queue.pop_back();
                    has_task = true;
                }
            }
            if (has_task) {
                try {
                    operation(task);
                } catch (std::exception e) {
                    std::cerr << e.what() << std::endl;
                    // put back in pool or move on
                }
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    }
};

} // namespace Threads
