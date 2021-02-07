//
// Created by egor on 07.02.2021.
//

#ifndef INC_3D_RENDERER_RENDERER_H
#define INC_3D_RENDERER_RENDERER_H

#include "world.h"
#include "screen.h"
#include "camera.h"
#include "primitives.h"

class Renderer {
public:
    Renderer(World* world, const Camera& camera);
    Screen Render() const;

private:
    // world
    World* world_;
    Camera camera_;

    std::vector<Triangle4D> Clip() const;
    std::vector<Triangle4D> ToCube(const std::vector<Triangle4D>&) const;
    void DrawTriangle(const Triangle4D& triangle, Screen& screen) const;
    int MapIntRange(double x, int range) const;
};
#endif //INC_3D_RENDERER_RENDERER_H
