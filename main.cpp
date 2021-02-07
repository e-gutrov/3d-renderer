#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "src/renderer.h"

int main() {
//    const int W = 640, H = 480;
    Renderer r(nullptr, Camera());
    auto screen = r.Render();
    sf::RenderWindow window(sf::VideoMode(screen.GetWidth(), screen.GetHeight()), "Test");
    sf::Clock clock;
    float lastTime = 0;
    while (window.isOpen()) {
        screen = r.Render();
        std::cout << "rendered" << '\n';
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
