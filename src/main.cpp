#include "load.hpp"
#include "png.hpp"
#include "process.hpp"
#include "threads.hpp"
#include <utility>

int main(const int argc, const char *argv[]) {
    if (argc < 2)
        throw std::runtime_error("Missing path to image directory");
    if (argc < 3)
        throw std::runtime_error("Missing path to target directory");
    std::string source_dir = argv[1];
    std::string target_dir = argv[2];

    int max_workers = (int)std::thread::hardware_concurrency();

    auto files = Load::ReadDirPngs(argv[1]);
    if (files.empty()) {
        throw std::runtime_error("Directory is empty");
    }

    auto runner = [&source_dir, &target_dir](const std::string &file) {
        Process::ProcessAndWrite(&Process::HorizontalFlip, file, source_dir,
                                 target_dir);
    };
    Threads::ThreadPool<std::string, decltype(runner)> thread_pool(
        max_workers, files, runner);
}
