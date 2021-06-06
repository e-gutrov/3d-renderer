#ifndef INC_3D_RENDERER_SCREEN_H
#define INC_3D_RENDERER_SCREEN_H

#include <Eigen/Core>
#include <vector>
#include "flat_primitives.h"
#include "primitives.h"

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
    constexpr const static double kZInf = 3000;
    int width_, height_;
    std::vector<Color> colors_;
    std::vector<double> z_;
};
}  // namespace Renderer
#endif  // INC_3D_RENDERER_SCREEN_H
