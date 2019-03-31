#include <iostream>
#include <regex>
extern "C" {
#include <dirent.h>
}

#include "../third_party/lodepng.h"
#include "load.hpp"

namespace Load {
std::vector<std::string> ReadDir(const char *dir) {
    std::string dir_path = dir;
    std::vector<std::string> files;
    DIR *dir_stream = dir_stream = opendir(dir);
    struct dirent *dirp;
    if (dir_stream == NULL) {
        throw std::runtime_error("Could not open directory for reading");
    }
    std::regex re{".*+\\.png"};
    while ((dirp = readdir(dir_stream)) != NULL) {
        if (std::regex_match(dirp->d_name, re)) {
            files.push_back(dir_path + "/" + std::string(dirp->d_name));
        }
    }
    return files;
}
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
