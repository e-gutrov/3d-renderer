#ifndef INC_3D_RENDERER_PRIMITIVES_H
#define INC_3D_RENDERER_PRIMITIVES_H

#include <Eigen/Core>
#include <SFML/Config.hpp>

namespace Renderer {
struct Color {
    sf::Uint8 r, g, b, a;
    Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
    static const Color Black;
};

struct Triangle4d {
    Eigen::Vector4d pts[3];
    Color color;

    Triangle4d(const Eigen::Vector3d& a, const Eigen::Vector3d& b,
               const Eigen::Vector3d& c, Color col);

    Triangle4d(const Eigen::Vector4d& a, const Eigen::Vector4d& b,
               const Eigen::Vector4d& c, Color col);

    Eigen::Vector3d GetNorm() const;
};

struct Line {
    Eigen::Vector3d dir = {1, 0, 0}, point = {0, 0, 0};

    Line() = default;

    Line(const Eigen::Vector3d& a, const Eigen::Vector3d& b);

    Line(const Eigen::Vector4d& a, const Eigen::Vector4d& b);
};

struct Plane {
    Eigen::Vector3d norm, point;

    explicit Plane(const Eigen::Vector3d& norm_);
    Plane(const Eigen::Vector3d& norm_, const Eigen::Vector3d& point_);

    explicit Plane(Triangle4d tr);

    double GetZ(double x, double y) const;

    double CountDistance(const Eigen::Vector3d& pt) const;

    Eigen::Vector3d Intersect(const Line& l) const;
};
}  // namespace Renderer
#endif  // INC_3D_RENDERER_PRIMITIVES_H
