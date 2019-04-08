#include "process.hpp"

namespace Process {

namespace {

template <typename Func>
void RunParallel(const int thread_cnt, png::png &image, Func operation) {
    if (image.image.empty())
        return;

    // TODO implement me:
    // - chunk image into rows
    // - start threads with `operation` to perform
    // - join and wait for threads to finish
}

void HorizontalFlipRange(png::png &image, int first, int end) {
    // process rows first to non-inclusive end
    while (first < end) {
        // width is no. pixels, each pixel is 4 bytes
        const auto start_offset = (image.width * 4) * first;

        // pointer to first byte of interest
        unsigned char *begin = image.image.data() + start_offset;
        // process bytes in terms of pixels (4 bytes)
        auto px_first = reinterpret_cast<png::pixel *>(begin);
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
    RunParallel(1, image, &HorizontalFlipRange);
}

void HorizontalFlip(int thread_cnt, png::png &image) {
    RunParallel(thread_cnt, image, &HorizontalFlipRange);
}
} // namespace Process
