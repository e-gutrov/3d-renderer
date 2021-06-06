#include "camera.h"

#include <unordered_map>

#include <Eigen/Geometry>

namespace Renderer {
using Eigen::Matrix3d;
using Eigen::Matrix4d;
using Eigen::Vector3d;

Camera::Camera(double E, double N)
    : E_(E), N_(N), Transform_(Matrix4d::Identity()) {}

void Camera::Rotate(Rotation rotation, double angle) {
    using Eigen::AngleAxisd;
    Matrix4d trans = Matrix4d::Identity();
    AngleAxisd angleAxis;
    switch (rotation) {
        case Rotation::Left:
            angleAxis = AngleAxisd(-angle, Vector3d(0, 1, 0));
            break;
        case Rotation::Right:
            angleAxis = AngleAxisd(angle, Vector3d(0, 1, 0));
            break;
        case Rotation::Down:
            angleAxis = AngleAxisd(-angle, Vector3d(1, 0, 0));
            break;
        case Rotation::Up:
            angleAxis = AngleAxisd(angle, Vector3d(1, 0, 0));
            break;
    }
    trans.block<3, 3>(0, 0) = angleAxis.matrix();
    Transform_ = trans * Transform_;
}

void Camera::Shift(Direction direction, double speed) {
    static const std::unordered_map<Direction, Eigen::Vector3d> directionToVector = {
            {Direction::Left, {-1, 0, 0}},
            {Direction::Right, {1, 0, 0}},
            {Direction::Down, {0, -1, 0}},
            {Direction::Up, {0, 1, 0}},
            {Direction::Backward, {0, 0, 1}},
            {Direction::Forward, {0, 0, -1}},
    };
    Matrix4d trans = Matrix4d::Identity();
    trans.block<3, 1>(0, 3) = -speed * directionToVector.at(direction);
    Transform_ = trans * Transform_;
}

Matrix4d Camera::GetMatrix() const { return Transform_; }

double Camera::GetE() const { return E_; }

double Camera::GetN() const { return N_; }
}  // namespace Renderer