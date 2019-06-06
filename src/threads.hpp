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
            // - start threads, give them `image_work` to do
            std::vector<std::thread> threads;
            for (auto start = 0; start < max_pool_size; ++start)
            {
              threads.emplace_back([this, operation](){ image_work(operation); });
            }

            // - poll for empty queue
            // - send shutdown signal to threads when queue is empty
            while (!queue.empty())
            {
              std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            shutdown = true;

            // - wait for threads to join
            for (auto& t : threads)
            {
              t.join();
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
        while (!shutdown)
        {
          std::unique_ptr<Task> taskPtr;
          {
            std::lock_guard<std::mutex> lock(pool_mutex);
            if (!queue.empty())
            {
              taskPtr = std::make_unique<Task>(queue.back());
              queue.pop_back();
            }
            else
            {
              std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
          }

          if (taskPtr)
            operation(*taskPtr);
        }
    }
};

} // namespace Threads
