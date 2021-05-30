#include "flat_primitives.h"
#include "screen.h"

namespace Renderer {
Vector2d::Vector2d(const Point2d &a, const Point2d &b)
    : x(b.x - a.x), y(b.y - a.y) {}

int Vector2d::CrossProduct(const Vector2d &other) const {
    return x * other.y - other.x * y;
}

Triangle2d::Triangle2d(const Point2d &a, const Point2d &b, const Point2d &c) {
    pts[0] = a;
    pts[1] = b;
    pts[2] = c;
}

Triangle2d::Triangle2d(const Triangle4d &triangle, const Screen &screen) {
    for (int i = 0; i < 3; ++i) {
        pts[i] =
            Point2d(screen.GetCoors(triangle.pts[i].x() / triangle.pts[i].w(),
                                    triangle.pts[i].y() / triangle.pts[i].w()));
    }
}

bool Triangle2d::TestPixel(const Point2d &pixel) const {
    int sum = 0;
    int sum1 = 0;
    for (int i = 0; i < 3; ++i) {
        sum += Vector2d({0, 0}, pts[i])
                   .CrossProduct(Vector2d({0, 0}, pts[(i + 1) % 3]));
        sum1 += abs(Vector2d(pixel, pts[i])
                        .CrossProduct(Vector2d(pixel, pts[(i + 1) % 3])));
    }
    sum = std::abs(sum);
    return abs(sum1) == sum;
}

std::pair<Point2d, Point2d> Triangle2d::BoundingBox() const {
    Point2d min{pts[0]}, max{pts[0]};

    for (int i = 1; i < 3; ++i) {
        min.x = std::min(min.x, pts[i].x);
        min.y = std::min(min.y, pts[i].y);

        max.x = std::max(max.x, pts[i].x);
        max.y = std::max(max.y, pts[i].y);
    }
    return {min, max};
}
}  // namespace Renderer