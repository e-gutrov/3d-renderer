//
// Created by egor on 07.02.2021.
//

#include "primitives.h"

Triangle4D::Triangle4D(const Eigen::Vector4d& a, const Eigen::Vector4d& b, const Eigen::Vector4d& c, Color col)
    : color(col) {
    pts[0] = a;
    pts[1] = b;
    pts[2] = c;
}
