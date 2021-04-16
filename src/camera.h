#ifndef INC_3D_RENDERER_CAMERA_H
#define INC_3D_RENDERER_CAMERA_H
#include <Core>

class Camera {
public:
    explicit Camera(double E = 1, double N = 1);
    void Rotate(const Eigen::Vector3d& rotation);
    void Shift(const Eigen::Vector3d& shift);
    Eigen::Matrix4d GetMatrix() const;
    double GetE() const;
    double GetN() const;

private:
    double E_, N_;
    Eigen::Matrix4d Transform_;
};
#endif //INC_3D_RENDERER_CAMERA_H
