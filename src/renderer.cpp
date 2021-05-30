#include <iostream>
#include <Eigen/Core>
#include "renderer.h"
#include "primitives.h"
#include "flat_primitives.h"

namespace Renderer {
    using Eigen::Vector3d;
    using Eigen::Vector4d;
    using Eigen::Matrix4d;

    void Renderer::Render(const World &world, const Camera &camera, Screen *screen) const {
        screen->Clear();
        int w = screen->GetWidth();
        int h = screen->GetHeight();

        auto triangles = ToCameraSpace(world, camera);
        triangles = Clip(triangles, camera, (double) h / w);
        triangles = ToCube(triangles, camera, (double) h / w);

        for (const auto &triangle : triangles) {
            DrawTriangle(triangle, screen);
        }
    }

    std::vector<Triangle4d> Renderer::ToCameraSpace(const World &world, const Camera &camera) const {
        auto result = world.GetObjects();
        auto trans = camera.GetMatrix();
        for (auto &triangle : result) {
            for (auto &pt : triangle.pts) {
                pt = trans * pt;
            }
        }
        return result;
    }

    std::vector<Triangle4d>
    Renderer::Clip(const std::vector<Triangle4d> &triangles, const Camera &camera, double aspect_ratio) const {
        std::vector<Triangle4d> result;
        double n = camera.GetN(), e = camera.GetE();
        std::vector<Plane> planes = {
                Plane(Vector3d(0, 0, -1), Vector3d(0, 0, n)),                    // near
                Plane(Vector3d(e / sqrt(e * e + 1), 0, -1 / sqrt(e * e + 1))),          // left
                Plane(Vector3d(-e / sqrt(e * e + 1), 0, -1 / sqrt(e * e + 1))),         // right
                Plane(Vector3d(
                        0,
                        e / sqrt(e * e + aspect_ratio * aspect_ratio),
                        -aspect_ratio / sqrt(e * e + aspect_ratio * aspect_ratio))),                     // bottom
                Plane(Vector3d(
                        0,
                        -e / sqrt(e * e + aspect_ratio * aspect_ratio),
                        -aspect_ratio / sqrt(e * e + aspect_ratio * aspect_ratio))),                     // top
        };
        for (const auto &tr : triangles) {
            std::vector<Vector4d> cur = {tr.pts[0], tr.pts[1], tr.pts[2]}, next;
            for (const auto &plane : planes) {
                for (int i = 0; i < cur.size(); ++i) {
                    const auto &p0 = cur[i], p1 = cur[(i + 1) % cur.size()];
                    double d0 = plane.Dist((p0 / p0.w()).head(3));
                    double d1 = plane.Dist((p1 / p1.w()).head(3));

                    if (d0 >= 0) {
                        next.emplace_back(p0);
                    }
                    if ((d0 >= 0 && d1 < 0) || (d0 < 0 && d1 > 0)) {
                        Vector4d pt;
                        pt.w() = 1;
                        pt.block<3, 1>(0, 0) = plane.Intersect(Line(p0, p1));
                        next.emplace_back(pt);
                    }
                }
                cur.swap(next);
                next.clear();
            }
            for (int i = 1; i + 1 < cur.size(); ++i) {
                result.emplace_back(cur[0], cur[i], cur[i + 1], tr.color);
            }
        }
        return result;
    }

    std::vector<Triangle4d>
    Renderer::ToCube(std::vector<Triangle4d> &triangles, const Camera &camera, double aspect_ratio) const {
        double n = camera.GetN(), e = camera.GetN();
        double l = -n / e, r = n / e;
        double b = -aspect_ratio * n / e, t = aspect_ratio * n / e;
        Matrix4d trans;
        trans << 2 * n / (r - l), 0, (r + l) / (r - l), 0,
                0, 2 * n / (t - b), (t + b) / (t - b), 0,
                0, 0, -1, -2 * n,
                0, 0, -1, 0;
        for (auto &triangle : triangles) {
            for (auto &pt : triangle.pts) {
                pt = trans * pt;
            }
        }
        return triangles;
    }

    void Renderer::DrawTriangle(const Triangle4d &triangle, Screen *screen) const {
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
}