//
// Created by egor on 07.02.2021.
//
#include <iostream>
#include <Core>
#include "renderer.h"
#include "primitives.h"
#include "flat_primitives.h"

Renderer::Renderer(World* world, const Camera& camera): world_(world), camera_(camera) {}

Screen Renderer::Render() const {
    const int W = 1920, H = 1080;
    Screen result(W, H);
    auto triangles = Clip();
    triangles = ToCube(triangles);

    for (const auto & triangle : triangles) {
        DrawTriangle(triangle, result);
    }
    return result;
}

std::vector<Triangle4D> Renderer::Clip() const {
    return {
        Triangle4D(
                Eigen::Vector4d(-1, -1, -1, 1),
                Eigen::Vector4d(1, -1, -1, 1),
                Eigen::Vector4d(1, 1, -1, 1),
                {0, 0, 0, 255}
        ),
//            Triangle4D(
//                    Eigen::Vector4d(0, 0, -1, 1),
//                    Eigen::Vector4d(0.5, 0.5, -1, 1),
//                    Eigen::Vector4d(-0.5, 0.5, -1, 1),
//                    {0, 0, 0, 255}
//            ),
    };
}

std::vector<Triangle4D> Renderer::ToCube(const std::vector<Triangle4D>& triangles) const {
    return triangles;
}

void Renderer::DrawTriangle(const Triangle4D &triangle, Screen& screen) const {
    Triangle2D screen_triangle(triangle, screen);
    auto box = screen_triangle.BoundingBox();

    box.second.x = std::min(box.second.x, screen.GetWidth() - 1);
    box.second.y = std::min(box.second.y, screen.GetHeight() - 1);
    for (int y = box.first.y; y <= box.second.y; ++y) {
        for (int x = box.first.x; x <= box.second.x; ++x) {
            if (screen_triangle.TestPixel({x, y})) {
                screen.SetPixel(y, x, -2, triangle.color);
            }
        }
    }
}