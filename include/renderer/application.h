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
    /**
     * @brief Constructs application
     * 
     * @param screenWidth Width of screen in pixels
     * @param screenHeight Height of screen in pixels
     * @param camera
     * @param shiftSpeed Speed that will be passed to camera's Shift() method
     * @param rotateSpeed Angle that will be passed to camera's Rotate() method
     */
    Application(int screenWidth, int screenHeight, Camera camera = Camera(),
                double shiftSpeed = 0.1, double rotateSpeed = 0.05);

    /**
     * @brief Launch application and listen for keyboard input
     */
    void Run();

    /**
     * @brief Add triangle to application's world
     * 
     * @param triangle Triangle to add
     */
    void AddObject(const Triangle4d& triangle);

    private:
    void Draw();

    void ProcessEvent(const sf::Event& event);

    void ProcessKeyPressedEvent(const sf::Event::KeyEvent& keyEvent);

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
