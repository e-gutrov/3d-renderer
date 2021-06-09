#include "obj_parser.cpp"
#include <iostream>
#include <Eigen/Core>
#include <renderer/application.h>

void PrepareWorld(Renderer::Application* app) {
    app->AddObject(Renderer::Triangle4d(
        Eigen::Vector4d(5, 0, -5, 1), Eigen::Vector4d(5, 2, -5, 1),
        Eigen::Vector4d(7, 2, -5, 1), {200, 0, 0, 255}));
    app->AddObject(Renderer::Triangle4d(
        Eigen::Vector4d(7, 0, -5, 1), Eigen::Vector4d(7, 2, -5, 1),
        Eigen::Vector4d(5, 0, -5, 1), {200, 0, 0, 255}));

    app->AddObject(Renderer::Triangle4d(
        Eigen::Vector4d(5, 0, -7, 1), Eigen::Vector4d(5, 2, -7, 1),
        Eigen::Vector4d(7, 2, -7, 1), {200, 200, 0, 255}));
    app->AddObject(Renderer::Triangle4d(
        Eigen::Vector4d(7, 0, -7, 1), Eigen::Vector4d(7, 2, -7, 1),
        Eigen::Vector4d(5, 0, -7, 1), {200, 200, 0, 255}));

    app->AddObject(Renderer::Triangle4d(
        Eigen::Vector4d(5, 0, -5, 1), Eigen::Vector4d(5, 2, -5, 1),
        Eigen::Vector4d(5, 0, -7, 1), {0, 0, 200, 255}));
    app->AddObject(Renderer::Triangle4d(
        Eigen::Vector4d(5, 0, -7, 1), Eigen::Vector4d(5, 2, -7, 1),
        Eigen::Vector4d(5, 2, -5, 1), {0, 0, 200, 255}));

    app->AddObject(Renderer::Triangle4d(
        Eigen::Vector4d(7, 0, -5, 1), Eigen::Vector4d(7, 2, -5, 1),
        Eigen::Vector4d(7, 0, -7, 1), {0, 200, 0, 255}));
    app->AddObject(Renderer::Triangle4d(
        Eigen::Vector4d(7, 0, -7, 1), Eigen::Vector4d(7, 2, -7, 1),
        Eigen::Vector4d(7, 2, -5, 1), {0, 200, 0, 255}));
}

void AddPyramid(Renderer::Application* app, double x, double z, double side) {
    using Eigen::Vector3d;
    using Renderer::Color;
    assert(app);
    double y = -1;

    z *= -1;
    auto middle = Vector3d(x + side / 2, y, z - side / 2);
    app->AddObject({
        Vector3d(x, 0, z),
        middle,
        Vector3d(x, 0, z - side),
        Color(255, 0, 0, 255)});
    app->AddObject({
        Vector3d(x, 0, z),
        middle,
        Vector3d(x + side, 0, z),
        Color(0, 255, 0, 255)});
    app->AddObject({
        Vector3d(x, 0, z - side),
        middle,
        Vector3d(x + side, 0, z - side),
        Color(0, 0, 255, 255)});
    app->AddObject({
        Vector3d(x + side, 0, z),
        middle,
        Vector3d(x + side, 0, z - side),
        Color(255, 255, 0, 255)});
}

void PrepareWorldWithManyTriangles(Renderer::Application* app, int rows, int cols) {
    assert(app);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            AddPyramid(app, j * 2, i * 2, 2);
        }
    }
}

void PrepareWorldFromOff(Renderer::Application* app, const std::string& filename) {
    auto triangles = ParseOff(filename);
    std::cerr << triangles.size() << std::endl;

    for (const auto& tr : triangles) {
        app->AddObject(tr);
    }
}

int main() {
    Renderer::Application app(640, 480, Renderer::Camera(0.01, 1.07), 0.01, 0.01);
//    PrepareWorld(&app);
//    PrepareWorldWithManyTriangles(&app, 10, 10);
    PrepareWorldFromOff(&app, "../teapot.off");
    app.Run();
    return 0;
}
