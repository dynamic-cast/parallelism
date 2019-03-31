#include <string>

#include "png.hpp"

namespace Load {
std::vector<std::string> ReadDir(const char *dir);
png::png ReadPng(const std::string &file_path);
void WritePng(const std::string &file_path, const png::png &image);
} // namespace Load
