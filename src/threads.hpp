#include <mutex>
#include <thread>
#include <vector>

namespace Threads {

template <typename Task, typename Func>
struct ThreadPool {
    ThreadPool(unsigned int _max_pool_size, Func operation)
        : max_pool_size(_max_pool_size) {
        ThreadPool(_max_pool_size, operation, {});
    }

    ThreadPool(unsigned int _max_pool_size, Func operation,
               std::vector<Task> tasks)
        : max_pool_size(_max_pool_size), queue(std::move(tasks)) {
        std::vector<std::thread> threads;
        for (int i = 0; i < max_pool_size; i++) {
            std::thread t(&work, operation);
            threads.emplace_back(std::move(t));
        }
        for (auto &thread : threads) {
            thread.join();
        }
    }
    ThreadPool(ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;

    void addTask(const Task &task) {
        std::lock_guard<std::mutex> lock(pool_mutex);
        queue.push_back(task);
    }

  private:
    bool shutdown = false;
    std::vector<Task> queue;
    std::mutex pool_mutex;

    unsigned int max_pool_size;
    void work(Func operation) {
        while (!shutdown) {
            Task task;
            bool has_task = false;
            if (!queue.empty()) {
                std::lock_guard<std::mutex> lock(pool_mutex);
                if (!queue.empty()) {
                    task = queue.pop_back();
                    has_task = true;
                }
            }
            if (has_task) {
                operation(task);
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    }
};

} // namespace Threads
