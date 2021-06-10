#ifndef INC_3D_RENDERER_WORLD_H
#define INC_3D_RENDERER_WORLD_H

#include <vector>
#include "primitives.h"

namespace Renderer {

/**
 * @brief Represents 3D scene and stores objects
 * 
 */
class World {
    public:
   	/**
   	 * @brief Adds triangle to world
   	 * 
   	 * @param tr Triangle to add
   	 */
    void AddObject(const Triangle4d &tr);

    /**
     * @brief Returns all triangles added to this world
     */
    const std::vector<Triangle4d>& GetObjects() const;

    private:
    std::vector<Triangle4d> objects_;
};
}  // namespace Renderer

#endif  // INC_3D_RENDERER_WORLD_H
