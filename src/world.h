//
// Created by egor on 07.02.2021.
//

#ifndef INC_3D_RENDERER_WORLD_H
#define INC_3D_RENDERER_WORLD_H

#include <vector>
#include "primitives.h"

class World {
public:
    void AddObject(const Triangle4D& tr);
    const std::vector<Triangle4D>& GetObjects() const;
private:
    std::vector<Triangle4D> objects_;
};

#endif //INC_3D_RENDERER_WORLD_H
