//
// Created by egor on 07.02.2021.
//

#ifndef INC_3D_RENDERER_SCREEN_H
#define INC_3D_RENDERER_SCREEN_H

#include <vector>
#include <Core>
#include "primitives.h"
#include "flat_primitives.h"

class Screen {
public:
    Screen(int width, int height);
    void Clear();
    void SetPixel(int row, int col, double z, Color c);
    int GetWidth() const;
    int GetHeight() const;
    const std::vector<Color>& GetColors() const;
    Point2D GetCoors(double x, double y) const;

private:
    constexpr const static double Z_INF = 3000;
    int width_, height_;
    std::vector<Color> colors_;
    std::vector<double> z_;
};
#endif //INC_3D_RENDERER_SCREEN_H
