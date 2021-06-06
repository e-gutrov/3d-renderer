//
// Created by egor on 25.04.2021.
//

#ifndef INC_3D_RENDERER_APPLICATION_H
#define INC_3D_RENDERER_APPLICATION_H

#include <SFML/Graphics.hpp>
#include "camera.h"
#include "renderer.h"
#include "screen.h"
#include "world.h"

namespace Renderer {
class Application {
    public:
    Application(int screenWidth, int screenHeight, Camera camera = Camera(),
                double shiftSpeed = 0.1, double rotateSpeed = 0.05);
    void Run();

    void AddObject(const Triangle4d &triangle);

    private:
    void Draw();

    void ProcessEvent(const sf::Event &event);

    void ProcessKeyPressedEvent(const sf::Event::KeyEvent &keyEvent);

    Screen screen_;
    World world_;
    Renderer renderer_;
    Camera camera_;

    sf::RenderWindow window_;
    sf::Texture texture_;
    sf::Sprite sprite_;

    double shiftSpeed_;
    double rotateSpeed_;
};
}  // namespace Renderer
#endif  // INC_3D_RENDERER_APPLICATION_H
