//
// Created by egor on 07.02.2021.
//

#include <iostream>
#include <Geometry>
#include "primitives.h"

Triangle4D::Triangle4D(const Eigen::Vector4d& a, const Eigen::Vector4d& b, const Eigen::Vector4d& c, Color col)
    : color(col) {
    pts[0] = a;
    pts[1] = b;
    pts[2] = c;
}

Plane::Plane(Eigen::Vector3d norm, double d): norm(norm), d(d) {}

Plane::Plane(Triangle4D tr) {
    for (auto & pt : tr.pts)
        pt /= pt.w();
    Eigen::Vector3d vec1 = (tr.pts[1] - tr.pts[0]).head(3);
    Eigen::Vector3d vec2 = (tr.pts[2] - tr.pts[0]).head(3);
    norm = vec1.cross(vec2);
    d = -norm.x() * tr.pts[0].x() - norm.y() * tr.pts[0].y() - norm.z() * tr.pts[0].z();
}

double Plane::GetZ(double x, double y) const {
    return (-norm.x() * x - norm.y() * y - d) / norm.z();
}