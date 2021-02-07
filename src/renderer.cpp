//
// Created by egor on 07.02.2021.
//
#include <Core>
#include "renderer.h"

Renderer::Renderer(World* world, const Camera& camera): world_(world), camera_(camera) {}

Screen Renderer::Render() const {
    const int W = 640, H = 480;
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
                Eigen::Vector4d(1, 1, -1, 1)
        ),
    };
}

std::vector<Triangle4D> Renderer::ToCube(const std::vector<Triangle4D>& triangles) const {
    return triangles;
}

int Renderer::MapIntRange(double x, int range) const {
    return static_cast<int>(round((x + 1) / 2 * range));
}

int Renderer::MapDoubleRange(int x, int range) const {

}

void Renderer::DrawTriangle(const Triangle4D &triangle, Screen& screen) const {
    auto box = triangle.BoundingBox();

    int min_x = MapIntRange(box.first.x(), screen.GetWidth());
    int max_x = MapIntRange(box.second.x(), screen.GetWidth());
    int min_y = MapIntRange(box.first.y(), screen.GetHeight());
    int max_y = MapIntRange(box.second.y(), screen.GetHeight());

    for (int x = min_x; x <= max_x; ++x) {
        for (int y = min_y; y <= max_y; ++y) {
            if (triangle.TestPoint(MapDoubleRange(x, screen.GetWidth()), MapDoubleRange(y, screen.GetHeight()))) {

            }
        }
    }
}