//
// Created by egor on 07.02.2021.
//
#include <iostream>
#include <Core>
#include "renderer.h"
#include "primitives.h"
#include "flat_primitives.h"

Renderer::Renderer(World* world, const Camera& camera): world_(world), camera_(camera) {}

Camera& Renderer::GetCamera() {
    return camera_;
}

Screen Renderer::Render() const {
    const int W = 1920, H = 1080;
    Screen result(W, H);
    auto triangles = ToCameraSpace();
    triangles = Clip(triangles);
    triangles = ToCube(triangles);

    for (const auto & triangle : triangles) {
        DrawTriangle(triangle, result);
        std::cout << "Triangle:\n";
        for (auto pt : triangle.pts) {
            std::cout << pt << '\n';
        }
    }
    return result;
}

std::vector<Triangle4D> Renderer::ToCameraSpace() const {
    auto result = world_->GetObjects();
    auto trans = camera_.GetMatrix();
    for (auto & triangle : result) {
        for (auto & pt : triangle.pts) {
            pt = trans * pt;
        }
    }
    return result;
}

std::vector<Triangle4D> Renderer::Clip(const std::vector<Triangle4D>& triangles) const {
    return triangles;
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
                screen.SetPixel(y, x, triangle.pts[0].z(), triangle.color);
            }
        }
    }
}