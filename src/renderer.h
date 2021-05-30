#ifndef INC_3D_RENDERER_RENDERER_H
#define INC_3D_RENDERER_RENDERER_H

#include "camera.h"
#include "primitives.h"
#include "screen.h"
#include "world.h"

namespace Renderer {
class Renderer {
    public:
    void Render(const World &world, const Camera &camera, Screen *screen) const;

    private:
    std::vector<Triangle4d> ToCameraSpace(const World &world,
                                          const Camera &camera) const;

    std::vector<Triangle4d> Clip(const std::vector<Triangle4d> &,
                                 const Camera &, double) const;

    std::vector<Triangle4d> ToCube(std::vector<Triangle4d> &, const Camera &,
                                   double) const;

    void DrawTriangle(const Triangle4d &triangle, Screen *screen) const;
};
}  // namespace Renderer
#endif  // INC_3D_RENDERER_RENDERER_H
