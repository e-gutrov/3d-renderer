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

/**
 * @brief Represents point of view. Renderer will render
 * scene with camera's view frustum
 */
class Camera {
    public:
    Camera() = default;

    /**
     * @brief Constructs camera by given near plane distance and horizontal field of view
     * 
     * @param nearPlaneDistance Distance to near plane
     * @param horizontalFov Horizontal field of view in radians
     */
    Camera(double nearPlaneDistance, double horizontalFov);

    /**
     * @brief Rotate camera to specified direction by angle
     * 
     * @param rotations
     * @param angle Angle in radians
     */
    void Rotate(Rotation rotation, double angle);

    /**
     * @brief Shifts camera to specified direction by speed
     * 
     * @param direction
     * @param speed
     */
    void Shift(Direction direction, double speed);

    /**
     * @brief Gets matrix for transforming from global coordinates to camera's
     */
    const Eigen::Matrix4d& GetMatrix() const;

    /**
     * @brief Gets camera's focal length
     */
    double GetFocalLength() const;

    /**
     * @brief Gets distance to near plane
     */
    double GetNearPlaneDistance() const;

    private:
    double focalLength_ = 1, nearPlaneDistance_ = 1;
    Eigen::Matrix4d transformMatrix_;
};
}  // namespace Renderer
#endif  // INC_3D_RENDERER_CAMERA_H
