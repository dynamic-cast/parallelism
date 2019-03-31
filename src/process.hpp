#include "png.hpp"
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <thread>

namespace Process {
void HorizontalFlip(png::png &image);
void HorizontalFlip(int thread_cnt, png::png &image);
} // namespace Process
