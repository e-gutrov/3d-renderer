#include "primitives.h"
#include <Eigen/Geometry>

namespace Renderer {
using Eigen::Vector3d;
using Eigen::Vector4d;

const Color Color::Black = Color(0, 0, 0, 255);

Triangle4d::Triangle4d(const Vector3d& a, const Vector3d& b, const Vector3d& c,
                       Color col)
    : color(col) {
    pts[0].block<3, 1>(0, 0) = a;
    pts[1].block<3, 1>(0, 0) = b;
    pts[2].block<3, 1>(0, 0) = c;
    for (auto &pt : pts) {
        pt.w() = 1;
    }
}

Triangle4d::Triangle4d(const Vector4d& a, const Vector4d& b, const Vector4d& c,
                       Color col)
    : color(col) {
    pts[0] = a;
    pts[1] = b;
    pts[2] = c;
    for (auto &pt : pts) {
        pt /= pt.w();
    }
}

Vector3d Triangle4d::GetNorm() const {
    Vector3d v1 = (pts[1] - pts[0]).head(3);
    Vector3d v2 = (pts[2] - pts[1]).head(3);
    return v1.cross(v2);
}

Line::Line(const Vector3d& a, const Vector3d& b) : dir(b - a), point(a) {}

Line::Line(const Vector4d& a, const Vector4d& b)
    : Line(static_cast<Vector3d>((a / a.w()).head(3)),
           static_cast<Vector3d>((b / b.w()).head(3))) {}

Plane::Plane(Triangle4d tr) {
    for (auto &pt : tr.pts) pt /= pt.w();
    Vector3d vec1 = (tr.pts[1] - tr.pts[0]).head(3);
    Vector3d vec2 = (tr.pts[2] - tr.pts[1]).head(3);
    norm = vec1.cross(vec2).normalized();
    point = tr.pts[0].head(3);
}

Plane::Plane(const Vector3d& norm_, const Vector3d& point_)
    : norm(norm_), point(point_) {}

double Plane::GetZ(double x, double y) const {
    double d = -norm.dot(point);
    return (-norm.x() * x - norm.y() * y - d) / norm.z();
}

Vector3d Plane::Intersect(const Line& l) const {
    double t = -(norm.dot(l.point) - norm.dot(point)) / norm.dot(l.dir);
    return l.point + t * l.dir;
}

double Plane::CountDistance(const Vector3d& pt) const {
    double d = -norm.dot(point);
    return norm.dot(pt) + d;
}
}  // namespace Renderer