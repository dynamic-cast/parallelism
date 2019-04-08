#include <iostream>

#include "load.hpp"
#include "png.hpp"
#include "process.hpp"

int main(const int argc, const char *argv[]) {
    if (argc < 2)
    {
        std::cerr << "Missing path to image" << std::endl;
        return 1;
    }

    std::string file_path = argv[1];

    std::string out_file = "processed.png";
    if (argc > 2)
        out_file = argv[2];

    int thread_count = (int)std::thread::hardware_concurrency();

    // load image into memory
    png::png image = Load::ReadPng(file_path);
    // process image
    Process::HorizontalFlip(thread_count, image);
    // write to disk
    Load::WritePng(out_file, image);
}
