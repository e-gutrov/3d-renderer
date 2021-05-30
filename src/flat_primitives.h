#ifndef INC_3D_RENDERER_FLAT_PRIMITIVES_H
#define INC_3D_RENDERER_FLAT_PRIMITIVES_H

#include "primitives.h"

namespace Renderer {
    struct Point2d {
        int x, y;
    };

    struct Vector2d {
        int x, y;

        Vector2d(const Point2d &a, const Point2d &b);

        int CrossProduct(const Vector2d &other) const;
    };

    class Screen;

    struct Triangle2d {
        Point2d pts[3];

        Triangle2d(const Point2d &a, const Point2d &b, const Point2d &c);

        Triangle2d(const Triangle4d &triangle, const Screen &screen);

        bool TestPixel(const Point2d &pixel) const;

        std::pair<Point2d, Point2d> BoundingBox() const;
    };
}
#endif //INC_3D_RENDERER_FLAT_PRIMITIVES_H
