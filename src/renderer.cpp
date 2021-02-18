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
    triangles = ToCube(triangles, 1, -1, 1, -1, 1);

    for (const auto & triangle : triangles) {
        DrawTriangle(triangle, result);
//        std::cout << "Triangle:\n";
//        for (auto pt : triangle.pts) {
//            std::cout << pt << '\n';
//        }
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

std::vector<Triangle4D> Renderer::ToCube(std::vector<Triangle4D>& triangles, double n, double l, double r, double b, double t) const {
    Eigen::Matrix4d trans = Eigen::Matrix4d::Identity();
    trans << 2 * n / (r - l), 0, (r + l) / (r - l), 0,
            0, 2 * n / (t - b), (t + b) / (t - b), 0,
            0, 0, -1, -2 * n,
            0, 0, -1, 0;
    for (auto & triangle : triangles) {
        std::cout << "Triangle\n";
        for (auto & pt : triangle.pts) {
            pt = trans * pt;
            std::cout << pt.transpose() / pt.w() << '\n';
        }
    }
    return triangles;
}

void Renderer::DrawTriangle(const Triangle4D &triangle, Screen& screen) const {
    Triangle2D screen_triangle(triangle, screen);
    auto box = screen_triangle.BoundingBox();

    box.second.x = std::min(box.second.x, screen.GetWidth() - 1);
    box.second.y = std::min(box.second.y, screen.GetHeight() - 1);
    Plane plane(triangle);
    for (int y = box.first.y; y <= box.second.y; ++y) {
        for (int x = box.first.x; x <= box.second.x; ++x) {
            if (screen_triangle.TestPixel({x, y})) {
//
//                screen.SetPixel(y, x, triangle.pts[0].z(), triangle.color);
                screen.SetPixel(y, x, plane.GetZ(x * 2.0 / screen.GetWidth() - 1, y * 2.0 / screen.GetHeight() - 1), triangle.color);
            }
        }
    }
}