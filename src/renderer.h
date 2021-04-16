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
    Screen Render(int w, int h, const Camera&) const;

private:
    World* World_;

    std::vector<Triangle4d> ToCameraSpace(const Camera& camera) const;
    std::vector<Triangle4d> Clip(const std::vector<Triangle4d>&, const Camera&, double) const;
    std::vector<Triangle4d> ToCube(std::vector<Triangle4d>&, const Camera&, double) const;
    void DrawTriangle(const Triangle4d& triangle, Screen* screen) const;
};
#endif //INC_3D_RENDERER_RENDERER_H
