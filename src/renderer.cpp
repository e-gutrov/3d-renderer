//
// Created by egor on 07.02.2021.
//
#include <iostream>
#include <Core>
#include "renderer.h"
#include "primitives.h"
#include "flat_primitives.h"

using namespace Eigen;

Renderer::Renderer(World* world, const Camera& camera): world_(world), camera_(camera) {}

Camera& Renderer::GetCamera() {
    return camera_;
}

Screen Renderer::Render() const {
    const int W = 640, H = 480;
    Screen result(W, H);
    auto triangles = ToCameraSpace();
    triangles = Clip(triangles, 3, (double)H / W, 1);
    triangles = ToCube(triangles, 2, (double)H / W, 1);

    for (const auto & triangle : triangles) {
        DrawTriangle(triangle, result);
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

std::vector<Triangle4D> Renderer::Clip(const std::vector<Triangle4D>& triangles, double e, double a, double n) const {
    std::vector<Triangle4D> result;
    double l = -n / e, r = n / e;
    double b = -a * n / e, t = a * n / e;
    std::vector<Plane> planes = {
            Plane(Vector3d(0, 0, -1), Vector3d(0, 0, n)),                    // near
            Plane(Vector3d(e / sqrt(e * e + 1), 0, -1 / sqrt(e * e + 1))),          // left
            Plane(Vector3d(-e / sqrt(e * e + 1), 0, -1 / sqrt(e * e + 1))),         // right
            Plane(Vector3d(0, e / sqrt(e * e + a * a), -a / sqrt(e * e + a * a))),  // bottom
            Plane(Vector3d(0, -e / sqrt(e * e + a * a), -a / sqrt(e * e + a * a))), // top
    };
    for (const auto & tr : triangles) {
        std::vector<Eigen::Vector4d> cur = {tr.pts[0], tr.pts[1], tr.pts[2]}, next;
        for (const auto & plane : planes) {
            for (int i = 0; i < cur.size(); ++i) {
                auto p0 = cur[i], p1 = cur[(i + 1) % cur.size()];
                if (plane.Dist((p0 / p0.w()).head(3)) >= 0) {
                    next.emplace_back(p0);
                    if (plane.Dist((p1 / p1.w()).head(3)) < 0) {
                        Eigen::Vector4d pt;
                        pt.w() = 1;
                        pt.block<3, 1>(0, 0) = plane.Intersect(Line(p0, p1));
                        next.emplace_back(pt);
                    }
                } else {
                    if (plane.Dist((p1 / p1.w()).head(3)) > 0) {
                        Eigen::Vector4d pt;
                        pt.w() = 1;
                        pt.block<3, 1>(0, 0) = plane.Intersect(Line(p0, p1));
                        next.emplace_back(pt);
                    }
                }
            }
            cur = next;
            next.clear();
        }
        for (int i = 1; i + 1 < cur.size(); ++i) {
            result.emplace_back(cur[0], cur[i], cur[i + 1], tr.color);
        }
    }
    return result;
}

std::vector<Triangle4D> Renderer::ToCube(std::vector<Triangle4D>& triangles, double e, double a, double n) const {
    double l = -n / e, r = n / e;
    double b = -a * n / e, t = a * n / e;
    Eigen::Matrix4d trans;
    trans << 2 * n / (r - l), 0, (r + l) / (r - l), 0,
            0, 2 * n / (t - b), (t + b) / (t - b), 0,
            0, 0, -1, -2 * n,
            0, 0, -1, 0;
    for (auto & triangle : triangles) {
        for (auto & pt : triangle.pts) {
            pt = trans * pt;
        }
    }
    return triangles;
}

void Renderer::DrawTriangle(const Triangle4D &triangle, Screen& screen) const {
    Triangle2D screen_triangle(triangle, screen);
    auto box = screen_triangle.BoundingBox();

//    box.first.x = std::max(box.first.x, 0);
//    box.first.y = std::max(box.first.y, 0);
    box.second.x = std::min(box.second.x, screen.GetWidth() - 1);
    box.second.y = std::min(box.second.y, screen.GetHeight() - 1);
    Plane plane(triangle);
    for (int y = box.first.y; y <= box.second.y; ++y) {
        for (int x = box.first.x; x <= box.second.x; ++x) {
            if (screen_triangle.TestPixel({x, y})) {
                double z = plane.GetZ(x * 2.0 / screen.GetWidth() - 1, y * 2.0 / screen.GetHeight() - 1);
                screen.SetPixel(y, x, z, triangle.color);
            }
        }
    }
}