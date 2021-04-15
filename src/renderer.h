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
    explicit Renderer(World* world);
    Screen Render(int W, int H, const Camera&) const;

private:
    World* world_;

    std::vector<Triangle4D> ToCameraSpace(const Camera& camera) const;
    std::vector<Triangle4D> Clip(const std::vector<Triangle4D>&, const Camera&, double) const;
    std::vector<Triangle4D> ToCube(std::vector<Triangle4D>&, const Camera&, double) const;
    void DrawTriangle(const Triangle4D& triangle, Screen* screen) const;
};
#endif //INC_3D_RENDERER_RENDERER_H
