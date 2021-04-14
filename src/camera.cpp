//
// Created by egor on 07.02.2021.
//
#include "camera.h"

#include <Geometry>
#include <utility>
#include <iostream>

Camera::Camera(Eigen::Vector3d pos, Eigen::Vector3d rotation):
    pos_(pos), rotation_(rotation) {}

void Camera::Rotate(const Eigen::Vector3d& rotation) {
    rotation_ += rotation;
}

void Camera::SetRotation(Eigen::Vector3d rotation) {
    rotation_ = rotation;
}

void Camera::Shift(const Eigen::Vector3d& shift) {
    Eigen::Vector4d shift4d;
    shift4d.head(3) << shift;
    shift4d.w() = 0;
    rotation_ = -rotation_;
    auto mat = GetMatrix();
    std::cout << mat << '\n' << shift4d << '\n';
    pos_ += (mat * shift4d).head(3);
    rotation_ = -rotation_;
}

void Camera::SetPos(Eigen::Vector3d pos) {
    pos_ = pos;
}

Eigen::Matrix4d Camera::GetMatrix() const {
    return (
            Eigen::AngleAxisd(rotation_.z(), Eigen::Vector3d(0, 0, 1))
            * Eigen::AngleAxisd(rotation_.y(), Eigen::Vector3d(0, 1, 0))
            * Eigen::AngleAxisd(rotation_.x(), Eigen::Vector3d(1, 0, 0))
            * Eigen::Translation3d(-pos_)
    ).matrix();
}