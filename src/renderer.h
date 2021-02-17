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
    Camera& GetCamera();

private:
    // world
    World* world_;
    Camera camera_;

    std::vector<Triangle4D> ToCameraSpace() const;
    std::vector<Triangle4D> Clip(const std::vector<Triangle4D>&) const;
    std::vector<Triangle4D> ToCube(std::vector<Triangle4D>&, double, double, double, double, double) const;
    void DrawTriangle(const Triangle4D& triangle, Screen& screen) const;
};
#endif //INC_3D_RENDERER_RENDERER_H
