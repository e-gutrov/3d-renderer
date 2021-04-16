//
// Created by egor on 07.02.2021.
//
#include "screen.h"

Screen::Screen(int width, int height)
    : Width_(width), Height_(height)
    , Colors_(Width_ * Height_)
    , Z_(Width_ * Height_, Z_INF) {}

void Screen::Clear() {
    Z_.assign(Width_ * Height_, Z_INF);
}

void Screen::SetPixel(int row, int col, double z, Color c) {
    int pos = row * Width_ + col;
    if (Z_[pos] > z) {
        Colors_[pos] = c;
        Z_[pos] = z;
    }
}

int Screen::GetWidth() const { return Width_; }

int Screen::GetHeight() const { return Height_; }

const std::vector<Color>& Screen::GetColors() const { return Colors_; }

Point2D Screen::GetCoors(double x, double y) const {
    return {static_cast<int>(round((x + 1) / 2 * Width_)),
            static_cast<int>(round((y + 1) / 2 * Height_))};
}
