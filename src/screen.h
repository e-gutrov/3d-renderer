#ifndef INC_3D_RENDERER_SCREEN_H
#define INC_3D_RENDERER_SCREEN_H

#include <vector>
#include <Core>
#include "primitives.h"
#include "flat_primitives.h"

namespace Renderer {
    class Screen {
    public:
        Screen(int width, int height);

        void Clear();

        void SetPixel(int row, int col, double z, const Color &c);

        int GetWidth() const;

        int GetHeight() const;

        const std::vector<Color> &GetColors() const;

        Point2d GetCoors(double x, double y) const;

    private:
        constexpr const static double Z_INF = 3000;
        int Width_, Height_;
        std::vector<Color> Colors_;
        std::vector<double> Z_;
    };
}
#endif //INC_3D_RENDERER_SCREEN_H
