#include "load.hpp"
#include "png.hpp"
#include "process.hpp"

int main(const int argc, const char *argv[]) {
    if (argc < 2)
        throw std::runtime_error("Missing path to image directory");
    if (argc < 3)
        throw std::runtime_error("Missing path to target directory");

    int MAX_THREADS = (int)std::thread::hardware_concurrency();

    std::cout << "Max number of threads to use: " << MAX_THREADS << std::endl;

    auto files = Load::ReadDir(argv[1]);
}
