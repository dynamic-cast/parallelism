#include <iostream>

#include "../third_party/lodepng.h"
#include "load.hpp"

namespace Load {
// read from disk
png::png ReadPng(const std::string &file_path) {
    png::png decoded;

    auto error = lodepng::decode(decoded.image, decoded.width, decoded.height,
                                 file_path);
    if (error) {
        std::cerr << error << std::endl;
        throw std::runtime_error("Could not load image.");
    }

    return decoded;
}
// write to disk
void WritePng(const std::string &file_path, const png::png &image) {
    unsigned error =
        lodepng::encode(file_path, image.image, image.width, image.height);
    if (error) {
        std::cerr << error << std::endl;
        throw std::runtime_error("Could not write image.");
    }
}
} // namespace Load
