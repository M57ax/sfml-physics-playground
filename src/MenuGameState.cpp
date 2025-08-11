#include "MenuGameState.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "PlayGameState.hpp"
#include "engine.hpp"
#include "gameState.hpp"

MenuGameState::MenuGameState(Engine& engine) : GameState(engine) {
    std::cout << "Menu State Constructor" << std::endl;
    circle.setRadius(100.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(sf::Vector2f(200.0f, 200.0f));
}

void MenuGameState::handleInput(Engine& engine, sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::H) {
            // engine.changeState();
            std::cout << "State wechseln...." << std::endl;
            engine.popState();
            engine.pushState(std::make_unique<PlayGameState>(engine));
        }
    }
    if (event.is<sf::Event::Closed>()) {
        engine.window.close();
    }
}

void MenuGameState::update(float deltatime, Engine& engine) {
}

void MenuGameState::draw(sf::RenderWindow& window) {
    window.draw(circle);
}
