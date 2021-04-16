//
// Created by egor on 07.02.2021.
//

#ifndef INC_3D_RENDERER_FLAT_PRIMITIVES_H
#define INC_3D_RENDERER_FLAT_PRIMITIVES_H

#include "primitives.h"

struct Point2D {
    int x, y;
};

struct Vec2D {
    int x, y;
    Vec2D(Point2D a, Point2D b);
    int CrossProduct(const Vec2D& other) const;
};

class Screen;

struct Triangle2D {
    Point2D pts[3];
    Triangle2D(const Point2D& a, const Point2D& b, const Point2D& c);
    Triangle2D(const Triangle4d& triangle, const Screen& screen);
    bool TestPixel(Point2D pixel) const;
    std::pair<Point2D, Point2D> BoundingBox() const;
};

#endif //INC_3D_RENDERER_FLAT_PRIMITIVES_H
