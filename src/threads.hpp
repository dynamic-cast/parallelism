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
            std::vector<std::thread> thread_pool;
            std::cout << "Hello Karenka!" << std::endl;
            for(unsigned i=0; i<max_pool_size; i++)
                thread_pool.push_back(std::thread(&ThreadPool::image_work, this, operation));
            // - poll for empty queue
            while(!queue.empty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            shutdown = true;
            for(auto& thread : thread_pool)
                thread.join();
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
        while(!shutdown) {
            std::unique_ptr<Task> task;
            {
                std::lock_guard<std::mutex> lock(pool_mutex);
                if(!queue.empty())
                {
                    task = std::make_unique<Task>(queue.back());
                    queue.pop_back();
                }
            }
                operation(*task);
            // - acquiring lock and task from `queue`
            // - performing `operation` on task
            // - sleeping when no work to be done
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        return;
    }
};

} // namespace Threads
