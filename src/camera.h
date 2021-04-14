//
// Created by egor on 07.02.2021.
//

#ifndef INC_3D_RENDERER_CAMERA_H
#define INC_3D_RENDERER_CAMERA_H
#include <Core>

class Camera {
public:
    explicit Camera();
    void Rotate(const Eigen::Vector3d& rotation);
    void Shift(const Eigen::Vector3d& shift);
    Eigen::Matrix4d GetMatrix() const;

private:
    Eigen::Matrix4d Transform_;
};
#endif //INC_3D_RENDERER_CAMERA_H
