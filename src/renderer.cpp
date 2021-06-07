#include "renderer.h"
#include <Eigen/Core>
#include <iostream>
#include "flat_primitives.h"
#include "primitives.h"

namespace Renderer {
using Eigen::Matrix4d;
using Eigen::Vector3d;
using Eigen::Vector4d;

void Renderer::Render(const World& world, const Camera& camera,
                      Screen* screen) const {
    assert(screen);

    screen->Clear();
    int w = screen->GetWidth();
    int h = screen->GetHeight();

    auto triangles = ToCameraSpace(world, camera);
    triangles = Clip(triangles, camera, (double)h / w);
    triangles = ToCube(triangles, camera, (double)h / w);
    std::cerr << "Started drawing" << std::endl;

    for (const auto& triangle : triangles) {
        DrawTriangle(triangle, screen);
    }
}

std::vector<Triangle4d> Renderer::ToCameraSpace(const World& world,
                                                const Camera& camera) const {
    auto result = world.GetObjects();
    auto trans = camera.GetMatrix();
    for (auto& triangle : result) {
        for (auto& pt : triangle.pts) {
            pt = trans * pt;
        }
    }
    return result;
}

std::vector<Triangle4d> Renderer::Clip(const std::vector<Triangle4d>& triangles,
                                       const Camera& camera,
                                       double aspect_ratio) const {
    std::vector<Triangle4d> result;
    std::vector<Plane> planes = {
        GetNearPlane(camera, aspect_ratio),
        GetLeftPlane(camera, aspect_ratio),
        GetRightPlane(camera, aspect_ratio),
        GetBottomPlane(camera, aspect_ratio),
        GetTopPlane(camera, aspect_ratio),
    };

    for (const auto& tr : triangles) {
        Polygon cur = ClipWithPlanes(planes, tr);
        for (int i = 1; i + 1 < cur.size(); ++i) {
            result.emplace_back(cur[0], cur[i], cur[i + 1], tr.color);
        }
    }
    return result;
}

std::vector<Triangle4d> Renderer::ToCube(std::vector<Triangle4d>& triangles,
                                         const Camera& camera,
                                         double aspect_ratio) const {
    auto trans = MakeProjectionMatrix(camera, aspect_ratio);
    for (auto& triangle : triangles) {
        for (auto& pt : triangle.pts) {
            pt = trans * pt;
        }
    }
    return triangles;
}

void Renderer::DrawTriangle(const Triangle4d& triangle, Screen* screen) const {
    assert(screen);
    Triangle2d screen_triangle(triangle, *screen);
    auto box = screen_triangle.BoundingBox();

    int w = screen->GetWidth();
    int h = screen->GetHeight();

    box.second.x = std::min(box.second.x, w - 1);
    box.second.y = std::min(box.second.y, h - 1);
    Plane plane(triangle);
    for (int y = box.first.y; y <= box.second.y; ++y) {
        for (int x = box.first.x; x <= box.second.x; ++x) {
            if (screen_triangle.TestPixel({x, y})) {
                double z = plane.GetZ(x * 2.0 / w - 1, y * 2.0 / h - 1);
                screen->SetPixel(y, x, z, triangle.color);
            }
        }
    }
}

Matrix4d Renderer::MakeProjectionMatrix(const Camera& camera, double aspect_ratio) {
    double n = camera.GetNearPlaneDistance(), e = camera.GetFocalLength();
    Matrix4d trans;
    trans << e, 0, 0, 0,
            0, e / aspect_ratio, 0, 0,
            0, 0, -1, -2 * n,
            0, 0, -1, 0;
    return trans;
}

Renderer::Polygon Renderer::ClipWithPlanes(const std::vector<Plane>& planes,
                                           const Triangle4d& tr) {
    Polygon cur = {tr.pts[0], tr.pts[1], tr.pts[2]}, next;
    for (const auto& plane : planes) {
        ClipWithPlane(plane, cur, &next);
        cur.swap(next);
        next.clear();
    }
    return cur;
}

void Renderer::ClipWithPlane(const Plane& plane, const Polygon& cur,
                             Polygon* result) {
    assert(result);
    for (int i = 0; i < cur.size(); ++i) {
        const auto& p0 = cur[i];
        const auto& p1 = cur[(i + 1) % cur.size()];
        double d0 = plane.CountDistance((p0 / p0.w()).head(3));
        double d1 = plane.CountDistance((p1 / p1.w()).head(3));

        if (d0 >= 0) {
            result->emplace_back(p0);
        }
        if ((d0 > 0 && d1 < 0) || (d0 < 0 && d1 > 0)) {
            Vector4d pt;
            pt.w() = 1;
            pt.block<3, 1>(0, 0) = plane.Intersect(Line(p0, p1));
            result->emplace_back(pt);
        }
    }
}

Plane Renderer::GetNearPlane(const Camera& camera, double aspect_ratio) const {
    return {Vector3d(0, 0, -1), Vector3d(0, 0, -camera.GetNearPlaneDistance())};
}

Plane Renderer::GetLeftPlane(const Camera& camera, double aspect_ratio) const {
    double e = camera.GetFocalLength();
    double coef = sqrt(e * e + 1);
    return Plane(Vector3d(e / coef, 0, -1 / coef));
}

Plane Renderer::GetRightPlane(const Camera& camera, double aspect_ratio) const {
    double e = camera.GetFocalLength();
    double coef = sqrt(e * e + 1);
    return Plane(Vector3d(-e / coef, 0, -1 / coef));
}

Plane Renderer::GetBottomPlane(const Camera& camera,
                               double aspect_ratio) const {
    double e = camera.GetFocalLength();
    double coef = sqrt(e * e + aspect_ratio * aspect_ratio);
    return Plane(Vector3d(0, e / coef, -aspect_ratio / coef));
}

Plane Renderer::GetTopPlane(const Camera& camera, double aspect_ratio) const {
    double e = camera.GetFocalLength();
    double coef = sqrt(e * e + aspect_ratio * aspect_ratio);
    return Plane(Vector3d(0, -e / coef, -aspect_ratio / coef));
}
}  // namespace Renderer