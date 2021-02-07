//
// Created by egor on 07.02.2021.
//

#ifndef INC_3D_RENDERER_PRIMITIVES_H
#define INC_3D_RENDERER_PRIMITIVES_H

#include <Core>

struct Color {
    int r = 240, g = 0, b = 0, a = 255;
};

struct Triangle4D {
    Eigen::Vector4d pts[3];
    Color color;

    Triangle4D(const Eigen::Vector4d& a, const Eigen::Vector4d&  b, const Eigen::Vector4d& c);
    std::pair<Eigen::Vector2d, Eigen::Vector2d> BoundingBox() const;
    bool TestPoint(double x, double y) const;
};

#endif //INC_3D_RENDERER_PRIMITIVES_H
