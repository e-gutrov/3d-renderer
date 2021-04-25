#include "camera.h"

#include <Geometry>

using Eigen::Vector3d;
using Eigen::Matrix3d;
using Eigen::Matrix4d;

Camera::Camera(double E, double N): E_(E), N_(N), Transform_(Matrix4d::Identity()) {}

void Camera::Rotate(const Vector3d& rotation) {
    using Eigen::AngleAxisd;

    Eigen::Matrix3d rotationMatrix = (AngleAxisd(rotation.z(), Vector3d(0, 0, 1))
                              * AngleAxisd(rotation.y(), Vector3d(0, 1, 0))
                              * AngleAxisd(rotation.x(), Vector3d(1, 0, 0))).matrix();
    Matrix4d trans = Matrix4d::Identity();
    trans.block<3, 3>(0, 0) = rotationMatrix;
    Transform_ = trans * Transform_;
}

void Camera::Shift(const Vector3d& shift) {
    Matrix4d trans = Matrix4d::Identity();
    trans.block<3, 1>(0, 3) = -shift;
    Transform_ = trans * Transform_;
}

Matrix4d Camera::GetMatrix() const {
    return Transform_;
}

double Camera::GetE() const {
    return E_;
}

double Camera::GetN() const {
    return N_;
}
