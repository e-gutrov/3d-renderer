//
// Created by egor on 07.02.2021.
//

#ifndef INC_3D_RENDERER_CAMERA_H
#define INC_3D_RENDERER_CAMERA_H
#include <Core>

class Camera {
public:
    explicit Camera(Eigen::Vector3d pos = Eigen::Vector3d::Zero(), Eigen::Vector3d rotation = Eigen::Vector3d::Zero());
    void Rotate(const Eigen::Vector3d& rotation);
    void SetRotation(Eigen::Vector3d rotation);
    void Shift(const Eigen::Vector3d& shift);
    void SetPos(Eigen::Vector3d pos);
    Eigen::Matrix4d GetMatrix() const;
private:
    Eigen::Vector3d pos_;
    Eigen::Vector3d rotation_;
};
#endif //INC_3D_RENDERER_CAMERA_H
