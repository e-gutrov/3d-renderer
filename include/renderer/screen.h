#ifndef INC_3D_RENDERER_SCREEN_H
#define INC_3D_RENDERER_SCREEN_H

#include <Eigen/Core>
#include <vector>
#include "flat_primitives.h"
#include "primitives.h"

namespace Renderer {

/**
 * @brief Represents pixel screen and stores 
 * color and z-buffer for each pixel
 */
class Screen {
    public:
    /**
     * @brief Constructs screen from its width and height
     * 
     * @param width Width of screen in pixels
     * @param height Height of screen in pixels
     */
    Screen(int width, int height);

    /**
     * @brief Resets z-buffer and fills it with black color
     */
    void Clear();

    /**
     * @brief Updates pixel with coordinates (row, col) with color c
     * depending on z coordinate
     * 
     * @param row Pixel row
     * @param col Pixel column
     * @param z Pixel z-value
     * @param c Pixel color
     */
    void SetPixel(int row, int col, double z, const Color& c);

    /**
     * @brief Gets width of screen
     */
    int GetWidth() const;

    /**
     * @brief Gets height of screen
     */
    int GetHeight() const;

    /**
     * @brief Gets vector of screen colors
     */
    const std::vector<Color>& GetColors() const;

    /**
     * @brief Gets screen coordinates by normalized x and y
     * 
     * @param x Double value in range [-1..1]
     * @param y Double value in range [-1..1]
     * 
     */
    Point2d GetCoordinates(double x, double y) const;

    private:
    constexpr const static double kZInf = 3000;
    int width_, height_;
    std::vector<Color> colors_;
    std::vector<double> z_;
};
}  // namespace Renderer
#endif  // INC_3D_RENDERER_SCREEN_H
