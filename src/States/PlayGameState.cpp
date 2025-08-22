#include "PlayGameState.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "../Entities/ball.hpp"
#include "../Entities/fps-counter.hpp"
#include "../UI/textButtons.hpp"
#include "../engine.hpp"
#include "MenuGameState.hpp"
#include "gameState.hpp"

PlayGameState::PlayGameState(Engine& engine) : GameState() {
    std::cout << "Play State" << std::endl;
    addEntity(std::make_unique<FpsCounter>(sf::Vector2f(10.f, 10.f)));
    // createBalls(engine);
    addEntity(std::make_unique<TextButton>(
        "Press 'B' to start", sf::Vector2f(635.f, 250.f), [](Engine& eng) {

        }));
}

void PlayGameState::handleInput(Engine& engine, sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
            std::cout << "State wechseln..." << std::endl;
            engine.changeState(std::make_unique<MenuGameState>(engine));
        }
    }
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::B) {
            std::cout << "create..." << std::endl;
            createBalls(engine);
        }
    }
    if (event.is<sf::Event::Closed>()) {
        engine.window.close();
    }
}
