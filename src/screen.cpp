//
// Created by egor on 07.02.2021.
//
#include "screen.h"

Screen::Screen(int width, int height)
    : width_(width), height_(height)
    , colors_(width_ * height_)
    , z_(width_ * height_) {}

void Screen::Clear() {
    for (auto & elem : z_) {
        elem = Z_INF;
    }
}

void Screen::SetPixel(int row, int col, double z, Color c) {
    int pos = row * width_ + col;
    if (z_[pos] > z) {
        colors_[pos] = c;
        z_[pos] = z;
    }
}

int Screen::GetWidth() const { return width_; }

int Screen::GetHeight() const { return height_; }

const std::vector<Color>& Screen::GetColors() const { return colors_; }

Point2D Screen::GetCoors(double x, double y) const {
    return {static_cast<int>(round((x + 1) / 2 * width_)),
            static_cast<int>(round((y + 1) / 2 * height_))};
}
