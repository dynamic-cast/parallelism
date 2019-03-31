#include <iostream>

#include "load.hpp"
#include "png.hpp"
#include "process.hpp"

int main(const int argc, const char *argv[]) {
    if (argc < 2)
        throw std::runtime_error("Missing path to image");

    std::string file_path = argv[1];

    std::string out_file = "processed.png";
    if (argc > 2)
        out_file = argv[2];

    int MAX_THREADS = (int)std::thread::hardware_concurrency() * 0.5;
    MAX_THREADS = 12;

    std::cout << "Max number of threads to use: " << MAX_THREADS << std::endl;

    // load image into memory
    png::png image = Load::ReadPng(file_path);
    // process image
    Process::HorizontalFlip(MAX_THREADS, image);
    // write to disk
    Load::WritePng(out_file, image);
}
