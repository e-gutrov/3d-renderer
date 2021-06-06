#ifndef INC_3D_RENDERER_WORLD_H
#define INC_3D_RENDERER_WORLD_H

#include <vector>
#include "primitives.h"

namespace Renderer {
class World {
    public:
    void AddObject(const Triangle4d &tr);

    const std::vector<Triangle4d> &GetObjects() const;

    private:
    std::vector<Triangle4d> objects_;
};
}  // namespace Renderer

#endif  // INC_3D_RENDERER_WORLD_H
