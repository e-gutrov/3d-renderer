#ifndef INC_3D_RENDERER_PRIMITIVES_H
#define INC_3D_RENDERER_PRIMITIVES_H

#include <Eigen/Core>
#include <SFML/Config.hpp>

namespace Renderer {
/**
 * @brief Represents RGBA color. Library depends on this layout
 * 
 */
struct Color {
    sf::Uint8 r, g, b, a;
    Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
    static const Color Black;
};

/**
 * @brief Represents colored triangle in projective coordinates
 * 
 */
struct Triangle4d {
    Eigen::Vector4d pts[3];
    Color color;

    /**
     * @brief Constructs triangle by 3 3D-points
     * 
     * @param a First point
     * @param b Second point
     * @param c Third point
     * @param col Color of triangle
     */
    Triangle4d(const Eigen::Vector3d& a, const Eigen::Vector3d& b,
               const Eigen::Vector3d& c, Color col);

    /**
     * @brief Constructs triangle by 3 points in projective coordinates
     * 
     * @param a First point
     * @param b Second point
     * @param c Third point
     * @param col Color of triangle
     */
    Triangle4d(const Eigen::Vector4d& a, const Eigen::Vector4d& b,
               const Eigen::Vector4d& c, Color col);
    // TODO
    Eigen::Vector3d GetNorm() const;
};

/**
 * @brief Represents a 3D-line
 */
struct Line {
    Eigen::Vector3d dir = {1, 0, 0}, point = {0, 0, 0};

    Line() = default;

    /**
     * @brief Constructs a line by two 3D-points on it
     * 
     * @param a First point
     * @param b Second point
     */
    Line(const Eigen::Vector3d& a, const Eigen::Vector3d& b);

    /**
     * @brief Constructs a line by two points in projective coordinates
     * 
     * @param a First point
     * @param b Second point
     */
    Line(const Eigen::Vector4d& a, const Eigen::Vector4d& b);
};

/**
 * @brief Represents a 3D-plane
 */
struct Plane {
    Eigen::Vector3d norm, point;

    /**
     * @brief Constructs a plane going through origin
     * with specified normal vector
     */
    explicit Plane(const Eigen::Vector3d& norm_);

    /**
     * @brief Constructs a plane going through point
     * with specified normal vector
     */
    Plane(const Eigen::Vector3d& norm_, const Eigen::Vector3d& point_);

    /**
     * @brief Constructs a plane going through specified triangle
     */
    explicit Plane(Triangle4d tr);

    /**
     * @brief Gets z-coordinate of point with specified (x, y) coordinates
     * 
     * @param x X-coordinate of point
     * @param y Y-coordinate of point
     */
    double GetZ(double x, double y) const;

    /**
     * @brief Counts oriented distance to specified point
     * @param pt Point
     */
    double CountDistance(const Eigen::Vector3d& pt) const;

    /**
     * @brief Returns intersection point of this plane and specified line
     * @param l Line for intersectcion
     */
    Eigen::Vector3d Intersect(const Line& l) const;
};
}  // namespace Renderer
#endif  // INC_3D_RENDERER_PRIMITIVES_H
