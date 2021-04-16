#ifndef INC_3D_RENDERER_PRIMITIVES_H
#define INC_3D_RENDERER_PRIMITIVES_H

#include <Core>
#include <SFML/Config.hpp>

struct Color {
    sf::Uint8 r = 0, g = 0, b = 0, a = 255;
};

struct Triangle4d {
    Eigen::Vector4d pts[3];
    Color color;

    Triangle4d(const Eigen::Vector3d& a, const Eigen::Vector3d&  b, const Eigen::Vector3d& c, Color col = Color());
    Triangle4d(const Eigen::Vector4d& a, const Eigen::Vector4d&  b, const Eigen::Vector4d& c, Color col = Color());
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

    explicit Plane(Eigen::Vector3d norm_, Eigen::Vector3d point_ = Eigen::Vector3d(0, 0, 0));
    explicit Plane(Triangle4d tr);

    double GetZ(double x, double y) const;
    double Dist(const Eigen::Vector3d& pt) const;
    Eigen::Vector3d Intersect(const Line& l) const;
};

#endif //INC_3D_RENDERER_PRIMITIVES_H
