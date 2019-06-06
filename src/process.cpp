#include "process.hpp"

#include <thread>
#include <future>

namespace Process {

namespace {

template <typename Func>
void RunParallel(const int threadCount, png::png& image, Func operation) {
    if (image.image.empty())
        return;

    // - chunk image into rows
    unsigned chunkSize = std::floor(image.height / threadCount);

    std::vector<std::thread> threads;
    // - start threads with `operation` to perform
    for (auto start = 0; start < image.height; start += chunkSize)
    {
        auto end = std::min(start + chunkSize, image.height);
        threads.emplace_back(operation, std::ref(image), start, end);
    }

    // - join and wait for threads to finish
    for (auto& t : threads)
    {
        t.join();
    }
}

template <typename Func>
void RunParallelAsync(const int threadCount, png::png& image, Func operation) {
    if (image.image.empty())
        return;

    // - chunk image into rows
    unsigned chunkSize = std::floor(image.height / threadCount);

    // - start threads with `operation` to perform
    for (auto start = 0; start < image.height; start += chunkSize)
    {
        auto end = std::min(start + chunkSize, image.height);
        std::async(operation, std::ref(image), start, end);
    }
}

void HorizontalFlipRange(png::png &image, int first, int end) {
    // process rows first to non-inclusive end
    while (first < end) {
        // width is no. pixels, each pixel is 4 bytes
        const auto start_offset = (image.width * 4) * first;

        // pointer to first byte of interest
        unsigned char *begin = image.image.data() + start_offset;
        // process bytes in terms of pixels (4 bytes)
        auto px_first = reinterpret_cast<png::pixel*>(begin);
        auto px_last = px_first + image.width - 1;

        while (px_first < px_last) {
            std::swap(*px_first, *px_last);
            px_first++;
            px_last--;
        }
        first++;
    }
}

} // namespace

void HorizontalFlip(png::png &image) {
    RunParallelAsync(1, image, &HorizontalFlipRange);
}

void HorizontalFlip(int thread_cnt, png::png &image) {
    RunParallelAsync(thread_cnt, image, &HorizontalFlipRange);
}
} // namespace Process
