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
            // TODO implement me
            // - start threads, give them `image_work` to do
            // - poll for empty queue
            // - send shutdown signal to threads when queue is empty
            // - wait for threads to join
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
        // TODO implement me:
        // - polling `queue` for work
        // - acquiring lock and task from `queue`
        // - performing `operation` on task
        // - sleeping when no work to be done
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
};

} // namespace Threads
