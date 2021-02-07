//
// Created by egor on 07.02.2021.
//
#include "flat_primitives.h"
#include "screen.h"

Vec2D::Vec2D(Point2D a, Point2D b): x(b.x - a.x), y(b.y - a.y) {}

int Vec2D::CrossProduct(const Vec2D &other) const {
    return x * other.y - other.x * y;
}

Triangle2D::Triangle2D(const Point2D& a, const Point2D& b, const Point2D& c) {
    pts[0] = a;
    pts[1] = b;
    pts[2] = c;
}

Triangle2D::Triangle2D(const Triangle4D& triangle, const Screen& screen) {
    for (int i = 0; i < 3; ++i) {
        pts[i] = Point2D(
                screen.GetCoors(triangle.pts[i].x() / triangle.pts[i].w(),
                                triangle.pts[i].y() / triangle.pts[i].w())
        );
    }
}

bool Triangle2D::TestPixel(Point2D pixel) const {
    int sum = 0;
    int sum1 = 0;
    for (int i = 0; i < 3; ++i) {
        sum += Vec2D({0, 0}, pts[i]).CrossProduct(Vec2D({0, 0}, pts[(i + 1) % 3]));
        sum1 += abs(Vec2D(pixel, pts[i]).CrossProduct(Vec2D(pixel, pts[(i + 1) % 3])));
    }
    sum = std::abs(sum);
    return abs(sum1) == sum;
}

std::pair<Point2D, Point2D> Triangle2D::BoundingBox() const {
    Point2D min{pts[0]}, max{pts[0]};

    for (int i = 1; i < 3; ++i) {
        min.x = std::min(min.x, pts[i].x);
        min.y = std::min(min.y, pts[i].y);

        max.x = std::max(max.x, pts[i].x);
        max.y = std::max(max.y, pts[i].y);
    }
    return {min, max};
}