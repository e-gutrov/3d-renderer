//
// Created by egor on 25.04.2021.
//
#include <iostream>
#include <utility>

#include "application.h"

namespace Renderer {
Application::Application(int screenWidth, int screenHeight, Camera camera,
                         double shiftSpeed, double rotateSpeed)
    : screen_(screenWidth, screenHeight)
    , camera_(std::move(camera))
    , window_(sf::VideoMode(screenWidth, screenHeight), "Renderer")
    , shiftSpeed_(shiftSpeed)
    , rotateSpeed_(rotateSpeed) {
    texture_.create(screenWidth, screenHeight);
    sprite_.setTexture(texture_);
}

void Application::Run() {
    while (window_.isOpen()) {
        Draw();
        sf::Event event;
        while (window_.pollEvent(event)) {
            ProcessEvent(event);
        }
    }
}

void Application::Draw() {
    renderer_.Render(world_, camera_, &screen_);
    texture_.update((sf::Uint8 *)screen_.GetColors().data());
    window_.draw(sprite_);
    window_.display();
}

void Application::AddObject(const Triangle4d& triangle) {
    world_.AddObject(triangle);
}

void Application::ProcessEvent(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::Closed:
            window_.close();
            break;
        case sf::Event::KeyPressed:
            ProcessKeyPressedEvent(event.key);
            break;
    }
}

void Application::ProcessKeyPressedEvent(const sf::Event::KeyEvent& keyEvent) {
    static constexpr const double default_speed = 0.1;
    static constexpr const double default_angle = 0.05;

    switch (keyEvent.code) {
        case sf::Keyboard::A:
            camera_.Shift(Direction::Left, default_speed);
            break;
        case sf::Keyboard::D:
            camera_.Shift(Direction::Right, default_speed);
            break;
        case sf::Keyboard::W:
            camera_.Shift(Direction::Forward, default_speed);
            break;
        case sf::Keyboard::S:
            camera_.Shift(Direction::Backward, default_speed);
            break;
        case sf::Keyboard::Up:
            camera_.Rotate(Rotation::Up, default_angle);
            break;
        case sf::Keyboard::Down:
            camera_.Rotate(Rotation::Down, default_angle);
            break;
        case sf::Keyboard::Left:
            camera_.Rotate(Rotation::Left, default_angle);
            break;
        case sf::Keyboard::Right:
            camera_.Rotate(Rotation::Right, default_angle);
            break;
    }
}
}  // namespace Renderer