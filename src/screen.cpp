#include "screen.h"

namespace Renderer {
Screen::Screen(int width, int height)
    : width_(width)
    , height_(height)
    , colors_(width_ * height_)
    , z_(width_ * height_, kZInf) {}

void Screen::Clear() {
    z_.assign(width_ * height_, kZInf);
    colors_.assign(width_ * height_, Color());
}

void Screen::SetPixel(int row, int col, double z, const Color &c) {
    int pos = row * width_ + col;
    if (z_[pos] > z) {
        colors_[pos] = c;
        z_[pos] = z;
    }
}

int Screen::GetWidth() const { return width_; }

int Screen::GetHeight() const { return height_; }

const std::vector<Color> &Screen::GetColors() const { return colors_; }

Point2d Screen::GetCoors(double x, double y) const {
    return {static_cast<int>(round((x + 1) / 2 * width_)),
            static_cast<int>(round((y + 1) / 2 * height_))};
}
}  // namespace Renderer