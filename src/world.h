//
// Created by egor on 07.02.2021.
//

#ifndef INC_3D_RENDERER_WORLD_H
#define INC_3D_RENDERER_WORLD_H

#include <vector>
#include "primitives.h"

class World {
public:
    void AddObject(const Triangle4d& tr);
    const std::vector<Triangle4d>& GetObjects() const;
private:
    std::vector<Triangle4d> Objects_;
};

#endif //INC_3D_RENDERER_WORLD_H
