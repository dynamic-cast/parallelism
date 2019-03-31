#include "png.hpp"
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <mutex>
#include <thread>

namespace Process {
void HorizontalFlip(png::png &image);
void HorizontalFlip(int thread_cnt, png::png &image);
void HorizontalFlip(std::vector<std::string> &images,
                    const std::string &out_dir);
} // namespace Process
