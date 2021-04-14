//
// Created by egor on 07.02.2021.
//

#ifndef INC_3D_RENDERER_PRIMITIVES_H
#define INC_3D_RENDERER_PRIMITIVES_H

#include <Core>

struct Color {
    int r = 0, g = 0, b = 0, a = 255;
};

struct Triangle4D {
    Eigen::Vector4d pts[3];
    Color color;

    Triangle4D(const Eigen::Vector4d& a, const Eigen::Vector4d&  b, const Eigen::Vector4d& c, Color col);
};

struct Line {
    Eigen::Vector3d dir = {1, 0, 0}, point = {0, 0, 0};

    Line() = default;
    Line(const Eigen::Vector3d& a, const Eigen::Vector3d& b);
    Line(const Eigen::Vector4d& a, const Eigen::Vector4d& b);
};

struct Plane {
    Eigen::Vector3d norm, point;

    explicit Plane(Triangle4D tr);

    double GetZ(double x, double y) const;
    double Dist(const Eigen::Vector3d& pt) const;
    Eigen::Vector3d Intersect(const Line& l) const;
};

#endif //INC_3D_RENDERER_PRIMITIVES_H
