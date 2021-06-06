//
// Created by egor on 25.04.2021.
//
#include <iostream>
#include <utility>

#include "application.h"

namespace Renderer {
Application::Application(int screenWidth, int screenHeight, Camera camera, double shiftSpeed, double rotateSpeed)
        : Screen_(screenWidth, screenHeight)
        , Camera_(std::move(camera))
        , Window_(sf::VideoMode(screenWidth, screenHeight), "Renderer")
        , shiftSpeed_(shiftSpeed)
        , rotateSpeed_(rotateSpeed) {
    Texture_.create(screenWidth, screenHeight);
    Sprite_.setTexture(Texture_);
}

void Application::Run() {
    while (Window_.isOpen()) {
        Draw();
        sf::Event event;
        while (Window_.pollEvent(event)) {
            ProcessEvent(event);
        }
    }
}

void Application::Draw() {
    Renderer_.Render(World_, Camera_, &Screen_);
    Texture_.update((sf::Uint8 *)Screen_.GetColors().data());
    Window_.draw(Sprite_);
    Window_.display();
}

void Application::AddObject(const Triangle4d &triangle) {
    World_.AddObject(triangle);
}

void Application::ProcessEvent(const sf::Event &event) {
    switch (event.type) {
        case sf::Event::Closed:
            Window_.close();
            break;
        case sf::Event::KeyPressed:
            ProcessKeyPressedEvent(event.key);
            break;
    }
}

void Application::ProcessKeyPressedEvent(const sf::Event::KeyEvent &keyEvent) {
    static constexpr const double default_speed = 0.1;
    static constexpr const double default_angle = 0.05;

    switch (keyEvent.code) {
        case sf::Keyboard::A:
            Camera_.Shift(Direction::Left, default_speed);
            break;
        case sf::Keyboard::D:
            Camera_.Shift(Direction::Right, default_speed);
            break;
        case sf::Keyboard::W:
            Camera_.Shift(Direction::Forward, default_speed);
            break;
        case sf::Keyboard::S:
            Camera_.Shift(Direction::Backward, default_speed);
            break;
        case sf::Keyboard::Up:
            Camera_.Rotate(Rotation::Up, default_angle);
            break;
        case sf::Keyboard::Down:
            Camera_.Rotate(Rotation::Down, default_angle);
            break;
        case sf::Keyboard::Left:
            Camera_.Rotate(Rotation::Left, default_angle);
            break;
        case sf::Keyboard::Right:
            Camera_.Rotate(Rotation::Right, default_angle);
            break;
    }
}
}  // namespace Renderer