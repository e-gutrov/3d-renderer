#ifndef INC_3D_RENDERER_CAMERA_H
#define INC_3D_RENDERER_CAMERA_H
#include <Eigen/Core>

namespace Renderer {
enum class Direction { Left, Right, Down, Up, Backward, Forward };

enum class Rotation {
    Left,
    Right,
    Down,
    Up,
    BarrelLeft,
    BarrelRight,
};
class Camera {
    public:
    Camera() = default;

    Camera(double nearPlaneDistance, double horizontalFov);

    void Rotate(Rotation rotation, double angle);

    void Shift(Direction direction, double speed);

    const Eigen::Matrix4d& GetMatrix() const;

    double GetFocalLength() const;

    double GetNearPlaneDistance() const;

    private:
    double focalLength_ = 1, nearPlaneDistance_ = 1;
    Eigen::Matrix4d transformMatrix_;
};
}  // namespace Renderer
#endif  // INC_3D_RENDERER_CAMERA_H
