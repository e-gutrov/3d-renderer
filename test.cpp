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
            Triangle4D(
                    Eigen::Vector4d(5, 0, -5, 1),
                    Eigen::Vector4d(5, 2, -5, 1),
                    Eigen::Vector4d(7, 2, -5, 1),
                    {200, 0, 0, 255}
    ));
    world.AddObject(
    Triangle4D(
            Eigen::Vector4d(7, 0, -5, 1),
            Eigen::Vector4d(7, 2, -5, 1),
            Eigen::Vector4d(5, 0, -5, 1),
            {200, 0, 0, 255}
    ));

    world.AddObject(
            Triangle4D(
                    Eigen::Vector4d(5, 0, -7, 1),
                    Eigen::Vector4d(5, 2, -7, 1),
                    Eigen::Vector4d(7, 2, -7, 1),
                    {200, 200, 0, 255}
            ));
    world.AddObject(
            Triangle4D(
                    Eigen::Vector4d(7, 0, -7, 1),
                    Eigen::Vector4d(7, 2, -7, 1),
                    Eigen::Vector4d(5, 0, -7, 1),
                    {200, 200, 0, 255}
            ));


    world.AddObject(
            Triangle4D(
                    Eigen::Vector4d(5, 0, -5, 1),
                    Eigen::Vector4d(5, 2, -5, 1),
                    Eigen::Vector4d(5, 0, -7, 1),
                    {0, 0, 200, 255}
            ));
    world.AddObject(
            Triangle4D(
                    Eigen::Vector4d(5, 0, -7, 1),
                    Eigen::Vector4d(5, 2, -7, 1),
                    Eigen::Vector4d(5, 2, -5, 1),
                    {0, 0, 200, 255}
            ));

    world.AddObject(
            Triangle4D(
                    Eigen::Vector4d(7, 0, -5, 1),
                    Eigen::Vector4d(7, 2, -5, 1),
                    Eigen::Vector4d(7, 0, -7, 1),
                    {0, 200, 0, 255}
            ));
    world.AddObject(
            Triangle4D(
                    Eigen::Vector4d(7, 0, -7, 1),
                    Eigen::Vector4d(7, 2, -7, 1),
                    Eigen::Vector4d(7, 2, -5, 1),
                    {0, 200, 0, 255}
            ));

    Renderer r(&world, Camera());
    r.GetCamera().Shift(Eigen::Vector3d(6, 1, 0));
//    r.GetCamera().SetPos(Eigen::Vector3d(6, 0, 0));
    auto screen = r.Render();
    sf::RenderWindow window(sf::VideoMode(screen.GetWidth(), screen.GetHeight()), "Test");
    sf::Clock clock;
    float lastTime = 0;
    while (window.isOpen()) {
        screen = r.Render();
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
                            r.GetCamera().Shift(Eigen::Vector3d(-0.1, 0, 0));
                            break;
                        case sf::Keyboard::D:
                            r.GetCamera().Shift(Eigen::Vector3d(0.1, 0, 0));
                            break;
                        case sf::Keyboard::W:
                            r.GetCamera().Shift(Eigen::Vector3d(0, 0, -0.1));
                            break;
                        case sf::Keyboard::S:
                            r.GetCamera().Shift(Eigen::Vector3d(0, 0, 0.1));
                            break;
                        case sf::Keyboard::Up:
                            r.GetCamera().Rotate(Eigen::Vector3d(0.1, 0, 0));
                            break;
                        case sf::Keyboard::Down:
                            r.GetCamera().Rotate(Eigen::Vector3d(-0.1, 0, 0));
                            break;
                        case sf::Keyboard::Left:
                            r.GetCamera().Rotate(Eigen::Vector3d(0, -0.1, 0));
                            break;
                        case sf::Keyboard::Right:
                            r.GetCamera().Rotate(Eigen::Vector3d(0, 0.1, 0));
                            break;
                    }
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
//        std::cout << fps << '\n';
        lastTime = currentTime;
    }
    return 0;
}
