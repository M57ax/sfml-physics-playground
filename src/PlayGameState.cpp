#include "PlayGameState.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "MenuGameState.hpp"
#include "ball.hpp"
#include "engine.hpp"
#include "fps-counter.hpp"
#include "gameState.hpp"

PlayGameState::PlayGameState(Engine& engine) : GameState(engine) {
    std::cout << "Play State" << std::endl;
    createBalls(engine);
}

void PlayGameState::handleInput(Engine& engine, sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
            std::cout << "State wechseln..." << std::endl;
            engine.changeState(std::make_unique<MenuGameState>(engine));
            engine.clearAll();
        }
    }
    if (event.is<sf::Event::Closed>()) {
        engine.window.close();
    }
}

void PlayGameState::update(float deltatime, Engine& engine) {
}

void PlayGameState::draw(sf::RenderWindow& window) {
}
