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
};
class Camera {
    public:
    explicit Camera(double E = 1, double N = 1);

    void Rotate(Rotation rotation, double angle);

    void Shift(Direction direction, double speed);

    Eigen::Matrix4d GetMatrix() const; // TODO: return const reference

    double GetE() const;

    double GetN() const;

    private:
    double E_, N_; // TODO
    Eigen::Matrix4d transformMatrix_;
};
}  // namespace Renderer
#endif  // INC_3D_RENDERER_CAMERA_H
