//
// Created by egor on 07.02.2021.
//

#include "primitives.h"

Triangle4D::Triangle4D(const Eigen::Vector4d& a, const Eigen::Vector4d& b, const Eigen::Vector4d& c) {
    pts[0] = a;
    pts[1] = b;
    pts[2] = c;
}

std::pair<Eigen::Vector2d, Eigen::Vector2d> Triangle4D::BoundingBox() const {
    double min_x, max_x, min_y, max_y;
    min_x = max_x = pts[0].x();
    min_y = max_y = pts[0].y();

    for (int i = 1; i < 3; ++i) {
        min_x = std::min(min_x, pts[i].x());
        max_x = std::max(max_x, pts[i].x());

        min_y = std::min(min_y, pts[i].y());
        max_y = std::max(max_y, pts[i].y());
    }
    return {Eigen::Vector2d(min_x, min_y), Eigen::Vector2d(max_x, max_y)};
}

bool Triangle4D::TestPoint(double x, double y) const {

}