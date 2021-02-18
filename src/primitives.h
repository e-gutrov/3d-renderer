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

struct Plane {
    Eigen::Vector3d norm;
    double d;

    explicit Plane(Eigen::Vector3d norm, double d = 0);
    Plane(Triangle4D tr);

    double GetZ(double x, double y) const;
    int DistSign(Eigen::Vector4d pt) const;
    Eigen::Vector4d Intersect() const;
};

#endif //INC_3D_RENDERER_PRIMITIVES_H
