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
    Application(int screenWidth, int screenHeight);

    void Run();

    void AddObject(const Triangle4d &triangle);

    Camera &GetCamera();

    private:
    void Draw();

    void ProcessEvent(const sf::Event &event);

    void ProcessKeyPressedEvent(const sf::Event::KeyEvent &keyEvent);

    Screen Screen_;
    World World_;
    Renderer Renderer_;
    Camera Camera_;

    sf::RenderWindow Window_;
    sf::Texture Texture_;
    sf::Sprite Sprite_;
};
}  // namespace Renderer
#endif  // INC_3D_RENDERER_APPLICATION_H
