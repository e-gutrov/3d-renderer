#include "application.h"

void PrepareWorld(Application* app) {
    app->AddObject(
            Triangle4d(
                    Eigen::Vector4d(5, 0, -5, 1),
                    Eigen::Vector4d(5, 2, -5, 1),
                    Eigen::Vector4d(7, 2, -5, 1),
                    {200, 0, 0, 255}));
    app->AddObject(
            Triangle4d(
                    Eigen::Vector4d(7, 0, -5, 1),
                    Eigen::Vector4d(7, 2, -5, 1),
                    Eigen::Vector4d(5, 0, -5, 1),
                    {200, 0, 0, 255}));

    app->AddObject(
            Triangle4d(
                    Eigen::Vector4d(5, 0, -7, 1),
                    Eigen::Vector4d(5, 2, -7, 1),
                    Eigen::Vector4d(7, 2, -7, 1),
                    {200, 200, 0, 255}));
    app->AddObject(
            Triangle4d(
                    Eigen::Vector4d(7, 0, -7, 1),
                    Eigen::Vector4d(7, 2, -7, 1),
                    Eigen::Vector4d(5, 0, -7, 1),
                    {200, 200, 0, 255}));


    app->AddObject(
            Triangle4d(
                    Eigen::Vector4d(5, 0, -5, 1),
                    Eigen::Vector4d(5, 2, -5, 1),
                    Eigen::Vector4d(5, 0, -7, 1),
                    {0, 0, 200, 255}));
    app->AddObject(
            Triangle4d(
                    Eigen::Vector4d(5, 0, -7, 1),
                    Eigen::Vector4d(5, 2, -7, 1),
                    Eigen::Vector4d(5, 2, -5, 1),
                    {0, 0, 200, 255}));

    app->AddObject(
            Triangle4d(
                    Eigen::Vector4d(7, 0, -5, 1),
                    Eigen::Vector4d(7, 2, -5, 1),
                    Eigen::Vector4d(7, 0, -7, 1),
                    {0, 200, 0, 255}));
    app->AddObject(
            Triangle4d(
                    Eigen::Vector4d(7, 0, -7, 1),
                    Eigen::Vector4d(7, 2, -7, 1),
                    Eigen::Vector4d(7, 2, -5, 1),
                    {0, 200, 0, 255}));
}

int main() {
    Application app(640, 480);
    PrepareWorld(&app);
    app.Run();
    return 0;
}
