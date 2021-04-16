#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Geometry>

#include "src/renderer.h"

int main() {
    const int W = 640, H = 480;
    World world;

    // testing projective
    world.AddObject(
            Triangle4d(
                    Eigen::Vector4d(5, 0, -5, 1),
                    Eigen::Vector4d(5, 2, -5, 1),
                    Eigen::Vector4d(7, 2, -5, 1),
                    {200, 0, 0, 255}
    ));
    world.AddObject(
    Triangle4d(
            Eigen::Vector4d(7, 0, -5, 1),
            Eigen::Vector4d(7, 2, -5, 1),
            Eigen::Vector4d(5, 0, -5, 1),
            {200, 0, 0, 255}
    ));

    world.AddObject(
            Triangle4d(
                    Eigen::Vector4d(5, 0, -7, 1),
                    Eigen::Vector4d(5, 2, -7, 1),
                    Eigen::Vector4d(7, 2, -7, 1),
                    {200, 200, 0, 255}
            ));
    world.AddObject(
            Triangle4d(
                    Eigen::Vector4d(7, 0, -7, 1),
                    Eigen::Vector4d(7, 2, -7, 1),
                    Eigen::Vector4d(5, 0, -7, 1),
                    {200, 200, 0, 255}
            ));


    world.AddObject(
            Triangle4d(
                    Eigen::Vector4d(5, 0, -5, 1),
                    Eigen::Vector4d(5, 2, -5, 1),
                    Eigen::Vector4d(5, 0, -7, 1),
                    {0, 0, 200, 255}
            ));
    world.AddObject(
            Triangle4d(
                    Eigen::Vector4d(5, 0, -7, 1),
                    Eigen::Vector4d(5, 2, -7, 1),
                    Eigen::Vector4d(5, 2, -5, 1),
                    {0, 0, 200, 255}
            ));

    world.AddObject(
            Triangle4d(
                    Eigen::Vector4d(7, 0, -5, 1),
                    Eigen::Vector4d(7, 2, -5, 1),
                    Eigen::Vector4d(7, 0, -7, 1),
                    {0, 200, 0, 255}
            ));
    world.AddObject(
            Triangle4d(
                    Eigen::Vector4d(7, 0, -7, 1),
                    Eigen::Vector4d(7, 2, -7, 1),
                    Eigen::Vector4d(7, 2, -5, 1),
                    {0, 200, 0, 255}
            ));

    Renderer r(&world);
    Camera cam;
    cam.Shift(Eigen::Vector3d(6, 1, 0));
    Screen screen(W, H);
    r.Render(cam, &screen);
    sf::RenderWindow window(sf::VideoMode(screen.GetWidth(), screen.GetHeight()), "Test");
    sf::Clock clock;
    float lastTime = 0;
    while (window.isOpen()) {
        r.Render(cam, &screen);
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::A:
                            cam.Shift(Eigen::Vector3d(-0.1, 0, 0));
                            break;
                        case sf::Keyboard::D:
                            cam.Shift(Eigen::Vector3d(0.1, 0, 0));
                            break;
                        case sf::Keyboard::W:
                            cam.Shift(Eigen::Vector3d(0, 0, -0.1));
                            break;
                        case sf::Keyboard::S:
                            cam.Shift(Eigen::Vector3d(0, 0, 0.1));
                            break;
                        case sf::Keyboard::Up:
                            cam.Rotate(Eigen::Vector3d(0.1, 0, 0));
                            break;
                        case sf::Keyboard::Down:
                            cam.Rotate(Eigen::Vector3d(-0.1, 0, 0));
                            break;
                        case sf::Keyboard::Left:
                            cam.Rotate(Eigen::Vector3d(0, -0.1, 0));
                            break;
                        case sf::Keyboard::Right:
                            cam.Rotate(Eigen::Vector3d(0, 0.1, 0));
                            break;
                    }
            }
        }

        sf::Texture texture;
        texture.create(screen.GetWidth(), screen.GetHeight());

        sf::Sprite sprite(texture);
        texture.update((sf::Uint8*)screen.GetColors().data());
        window.draw(sprite);

        window.display();
        float currentTime = clock.getElapsedTime().asSeconds();
        float fps = 1.f / (currentTime - lastTime);
        std::cout << fps << '\n';
        lastTime = currentTime;
    }
    return 0;
}
