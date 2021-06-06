#ifndef INC_3D_RENDERER_RENDERER_H
#define INC_3D_RENDERER_RENDERER_H

#include "camera.h"
#include "primitives.h"
#include "screen.h"
#include "world.h"

namespace Renderer {
class Renderer {
    public:
    void Render(const World& world, const Camera& camera, Screen* screen) const;

    private:
    std::vector<Triangle4d> ToCameraSpace(const World& world,
                                          const Camera& camera) const;

    std::vector<Triangle4d> Clip(const std::vector<Triangle4d>&,
                                 const Camera&, double) const;

    std::vector<Triangle4d> ToCube(std::vector<Triangle4d>&, const Camera&,
                                   double) const;

    void DrawTriangle(const Triangle4d& triangle, Screen* screen) const;

private:
    using Polygon = std::vector<Eigen::Vector4d>;
    static Eigen::Matrix4d MakeProjectionMatrix(const Camera& camera, double aspect_ratio);

    static Polygon ClipWithPlanes(const std::vector<Plane>& planes, const Triangle4d& tr);
    static void ClipWithPlane(const Plane& plane, const Polygon& cur, Polygon* result);

    Plane GetNearPlane(const Camera& camera, double aspect_ratio) const;
    Plane GetLeftPlane(const Camera& camera, double aspect_ratio) const;
    Plane GetRightPlane(const Camera& camera, double aspect_ratio) const;
    Plane GetBottomPlane(const Camera& camera, double aspect_ratio) const;
    Plane GetTopPlane(const Camera& camera, double aspect_ratio) const;
};
}  // namespace Renderer
#endif  // INC_3D_RENDERER_RENDERER_H
