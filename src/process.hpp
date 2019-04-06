#include "load.hpp"
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

template <typename Func>
void ProcessAndWrite(Func operation, const std::string &file,
                     const std::string &source_dir,
                     const std::string &target_dir) {
    std::string _source = source_dir + '/' + file;
    std::string _target = target_dir + '/' + file;
    auto png = Load::ReadPng(_source);
    operation(png);
    Load::WritePng(_target, png);
}
} // namespace Process
