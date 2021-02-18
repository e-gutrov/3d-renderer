#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Geometry>

#include "src/renderer.h"

int main() {
    const int W = 640, H = 480;
    World world;
    /*
    // three flat triangles
    world.AddObject(Triangle4D(
            Eigen::Vector4d(-0.5, -0.5, -0.25, 1),
            Eigen::Vector4d(0.5, -0.5, -0.25, 1),
            Eigen::Vector4d(0.5, 0.5, -0.25, 1),
            {0, 0, 0, 255}
    ));
    world.AddObject(Triangle4D(
            Eigen::Vector4d(-0.25, -0.25, -0.5, 1),
            Eigen::Vector4d(-0.25, 0.25, -0.5, 1),
            Eigen::Vector4d(0.25, 0.25, -0.5, 1),
            {0, 200, 0, 255}
    ));
    world.AddObject(Triangle4D(
            Eigen::Vector4d(-0.25, 0.25, -0.45, 1),
            Eigen::Vector4d(0.4, -0.5, -0.45, 1),
            Eigen::Vector4d(0.5, -0.4, -0.45, 1),
            {200, 200, 100, 255}
    ));
    // end of three flat triangles
    */

//    world.AddObject(
//            Triangle4D(
//                    Eigen::Vector4d(-0.5, -0.5, 0.5, 1),
//                    Eigen::Vector4d(0.5, -0.5, 0.5, 1),
//                    Eigen::Vector4d(0, 0.5, 0.5, 1),
//                    {200, 0, 0, 255}
//    ));
//    world.AddObject(
//            Triangle4D(
//                    Eigen::Vector4d(0.5, -0.5, 0.5, 1),
//                    Eigen::Vector4d(0.5, -0.5, -0.5, 1),
//                    Eigen::Vector4d(0.5, 0.5, 0, 1),
//                    {0, 200, 0, 255}
//    ));
//    world.AddObject(
//            Triangle4D(
//                    Eigen::Vector4d(-0.5, -0.5, -0.5, 1),
//                    Eigen::Vector4d(0.5, -0.5, -0.5, 1),
//                    Eigen::Vector4d(0, 0.5, -0.5, 1),
//                    {0, 0, 200, 255}
//    ));
//    world.AddObject(
//            Triangle4D(
//                    Eigen::Vector4d(-0.5, -0.5, 0.5, 1),
//                    Eigen::Vector4d(-0.5, -0.5, -0.5, 1),
//                    Eigen::Vector4d(-0.5, 0.5, 0, 1),
//                    {0, 200, 200, 255}
//    ));


//    Plane pl_red(Triangle4D(
//            Eigen::Vector4d(-0.224804, 0, 0.574732, 1),
//            Eigen::Vector4d(0.194436, 0, 0.585787, 1),
//            Eigen::Vector4d(-0.0124231, 0.209834, 0.580333, 1),
//            {200, 0, 0, 255}
//    ));
//    Plane pl_blue(Triangle4D(
//            Eigen::Vector4d(-0.224804, 0, 0.574732, 1),
//            Eigen::Vector4d(-0.176557, 0, 0.701447, 1),
//            Eigen::Vector4d(-0.196457,  0.175409,  0.649181, 1),
//            {0, 0, 200, 255}
//    ));
//    std::cout << "red: " << pl_red.GetZ(-0.21, 0) << '\n' << "blue: " << pl_blue.GetZ(-0.21, 0);
//    return 0;
    // testing projective
//    world.AddObject(
//            Triangle4D(
//                    Eigen::Vector4d(5, 0, -5, 1),
//                    Eigen::Vector4d(7, 0, -5, 1),
//                    Eigen::Vector4d(6, 1, -5, 1),
//                    {200, 0, 0, 255}
//    ));
//    world.AddObject(
//            Triangle4D(
//                    Eigen::Vector4d(5, 0, -7, 1),
//                    Eigen::Vector4d(7, 0, -7, 1),
//                    Eigen::Vector4d(6, 1, -7, 1),
//                    {200, 200, 0, 255}
//            ));
//    world.AddObject(
//            Triangle4D(
//                    Eigen::Vector4d(5, 0, -5, 1),
//                    Eigen::Vector4d(5, 0, -7, 1),
//                    Eigen::Vector4d(5, 1, -6, 1),
//                    {0, 0, 200, 255}
//            ));
//    world.AddObject(
//            Triangle4D(
//                    Eigen::Vector4d(7, 0, -5, 1),
//                    Eigen::Vector4d(7, 0, -7, 1),
//                    Eigen::Vector4d(7, 1, -6, 1),
//                    {0, 200, 0, 255}
//    ));
    // testing coverage
//    world.AddObject(
//            Triangle4D(
//                    Eigen::Vector4d(5, 0, -5, 1),
//                    Eigen::Vector4d(6, 1, -6, 1),
//                    Eigen::Vector4d(7, 0, -7, 1),
//                    {0, 200, 0, 255}
//    ));
//    world.AddObject(Triangle4D(
//            Eigen::Vector4d(7, -1, -5, 1),
//            Eigen::Vector4d(6, 1, -6, 1),
//            Eigen::Vector4d(5, -1, -7, 1),
//            {200, 200, 0, 255}
//    ));
    // testing cube


    Renderer r(&world, Camera());

    auto screen = r.Render();
    sf::RenderWindow window(sf::VideoMode(screen.GetWidth(), screen.GetHeight()), "Test");
    sf::Clock clock;
    float lastTime = 0;
    r.GetCamera().SetPos(Eigen::Vector3d(6, 0, 0));
    while (window.isOpen()) {
        screen = r.Render();
        r.GetCamera().Shift(Eigen::Vector3d(-6.0 / 50, 0, -6.0 / 50));
        r.GetCamera().Rotate(Eigen::Vector3d(0, 1.57 / 50, 0));
//        std::cout << "rendered" << '\n';
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        auto pixels = std::make_unique<sf::Uint8[]>(screen.GetWidth() * screen.GetHeight() * 4);
        sf::Texture texture;
        texture.create(screen.GetWidth(), screen.GetHeight());

        sf::Sprite sprite(texture);
        for (int i = 0; i < screen.GetWidth() * screen.GetHeight(); ++i) {
            pixels[4 * i] = screen.GetColors()[i].r;
            pixels[4 * i + 1] = screen.GetColors()[i].g;
            pixels[4 * i + 2] = screen.GetColors()[i].b;
            pixels[4 * i + 3] = screen.GetColors()[i].a;
        }
        texture.update(pixels.get());


        window.draw(sprite);

        window.display();
        float currentTime = clock.getElapsedTime().asSeconds();
        float fps = 1.f / (currentTime - lastTime);
        std::cout << fps << '\n';
        lastTime = currentTime;
    }
    return 0;
}
