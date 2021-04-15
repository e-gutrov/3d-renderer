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
    for (int i = 0; i < 3; ++i) {
        pts[i] /= pts[i].w();
    }
}

Eigen::Vector3d Triangle4D::GetNorm() const {
    Eigen::Vector3d v1 = (pts[1] - pts[0]).head(3);
    Eigen::Vector3d v2 = (pts[2] - pts[1]).head(3);
    return v1.cross(v2);
}

Line::Line(const Eigen::Vector3d& a, const Eigen::Vector3d& b)
    : dir(b - a), point(a) {}

Line::Line(const Eigen::Vector4d& a, const Eigen::Vector4d& b)
    : Line(
            static_cast<Eigen::Vector3d>((a / a.w()).head(3)),
            static_cast<Eigen::Vector3d>((b / b.w()).head(3))) {}

Plane::Plane(Triangle4D tr) {
    for (auto & pt : tr.pts)
        pt /= pt.w();
    Eigen::Vector3d vec1 = (tr.pts[1] - tr.pts[0]).head(3);
    Eigen::Vector3d vec2 = (tr.pts[2] - tr.pts[1]).head(3);
    norm = vec1.cross(vec2).normalized();
    point = tr.pts[0].head(3);
}

Plane::Plane(Eigen::Vector3d norm_, Eigen::Vector3d point_) : norm(norm_), point(point_) {}

double Plane::GetZ(double x, double y) const {
    double d = -norm.dot(point);
    return (-norm.x() * x - norm.y() * y - d) / norm.z();
}

Eigen::Vector3d Plane::Intersect(const Line& l) const {
    double t = -(norm.dot(l.point) - norm.dot(point)) / norm.dot(l.dir);
    return l.point + t * l.dir;
}

double Plane::Dist(const Eigen::Vector3d& pt) const {
    double d = -norm.dot(point);
    return norm.dot(pt) + d;
}
