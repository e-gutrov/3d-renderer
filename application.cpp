//
// Created by egor on 25.04.2021.
//
#include <iostream>

#include "application.h"

Application::Application(int screenWidth, int screenHeight)
    : Screen_(screenWidth, screenHeight)
    , Window_(sf::VideoMode(screenWidth, screenHeight), "Test" /* TODO */) {

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
    Texture_.update((sf::Uint8*)Screen_.GetColors().data());
    Window_.draw(Sprite_);
    Window_.display();
}

void Application::AddObject(const Triangle4d &triangle) {
    World_.AddObject(triangle);
}

void Application::ProcessEvent(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::Closed:
            Window_.close();
            break;
        case sf::Event::KeyPressed:
            ProcessKeyPressedEvent(event.key);
            break;
    }
}

void Application::ProcessKeyPressedEvent(const sf::Event::KeyEvent& keyEvent) {
    switch (keyEvent.code) {
        case sf::Keyboard::A:
            Camera_.Shift(Eigen::Vector3d(-0.1, 0, 0));
            break;
        case sf::Keyboard::D:
            Camera_.Shift(Eigen::Vector3d(0.1, 0, 0));
            break;
        case sf::Keyboard::W:
            Camera_.Shift(Eigen::Vector3d(0, 0, -0.1));
            break;
        case sf::Keyboard::S:
            Camera_.Shift(Eigen::Vector3d(0, 0, 0.1));
            break;
        case sf::Keyboard::Up:
            Camera_.Rotate(Eigen::Vector3d(0.1, 0, 0));
            break;
        case sf::Keyboard::Down:
            Camera_.Rotate(Eigen::Vector3d(-0.1, 0, 0));
            break;
        case sf::Keyboard::Left:
            Camera_.Rotate(Eigen::Vector3d(0, -0.1, 0));
            break;
        case sf::Keyboard::Right:
            Camera_.Rotate(Eigen::Vector3d(0, 0.1, 0));
            break;
    }
}

Camera& Application::GetCamera() {
    return Camera_;
}
