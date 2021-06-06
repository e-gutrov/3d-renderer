#include "camera.h"

#include <unordered_map>

#include <Eigen/Geometry>

namespace Renderer {
using Eigen::Matrix3d;
using Eigen::Matrix4d;
using Eigen::Vector3d;

Camera::Camera(double E, double N)
    : E_(E), N_(N), transformMatrix_(Matrix4d::Identity()) {}

void Camera::Rotate(Rotation rotation, double angle) {
    using Eigen::AngleAxisd;
    static const Vector3d rotateLeftRightAxis(0, 1, 0);
    static const Vector3d rotateUpDownAxis(1, 0, 0);

    Matrix4d trans = Matrix4d::Identity();
    AngleAxisd angleAxis;
    switch (rotation) {
        case Rotation::Left:
            angleAxis = AngleAxisd(-angle, rotateLeftRightAxis);
            break;
        case Rotation::Right:
            angleAxis = AngleAxisd(angle, rotateLeftRightAxis);
            break;
        case Rotation::Down:
            angleAxis = AngleAxisd(-angle, rotateUpDownAxis);
            break;
        case Rotation::Up:
            angleAxis = AngleAxisd(angle, rotateUpDownAxis);
            break;
    }
    trans.block<3, 3>(0, 0) = angleAxis.matrix();
    transformMatrix_ = trans * transformMatrix_;
}

void Camera::Shift(Direction direction, double speed) {
    static const std::unordered_map<Direction, Eigen::Vector3d>
        directionToVector = {
            {Direction::Left, {-1, 0, 0}},    {Direction::Right, {1, 0, 0}},
            {Direction::Down, {0, -1, 0}},    {Direction::Up, {0, 1, 0}},
            {Direction::Backward, {0, 0, 1}}, {Direction::Forward, {0, 0, -1}},
        };
    Matrix4d trans = Matrix4d::Identity();
    trans.block<3, 1>(0, 3) = -speed * directionToVector.at(direction);
    transformMatrix_ = trans * transformMatrix_;
}

Matrix4d Camera::GetMatrix() const { return transformMatrix_; }

double Camera::GetE() const { return E_; }

double Camera::GetN() const { return N_; }
}  // namespace Renderer