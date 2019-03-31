#ifndef PNG_HPP
#define PNG_HPP

#include <mutex>
#include <vector>

namespace png {
struct pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct png {
    // ctors
    png() = default;
    png(unsigned w, unsigned h) : width(w), height(h) {
        image.reserve(w * h * 4);
    }
    png(const png &_png) = default;
    png(png &&_png) = default;

    // members
    std::vector<unsigned char> image;
    unsigned width;
    unsigned height;
};
} // namespace png
#endif // PNG_HPP
