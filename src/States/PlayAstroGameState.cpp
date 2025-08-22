#include "PlayAstroGameState.hpp"

#include <iostream>

#include "../Entities/food.hpp"
#include "../Entities/fps-counter.hpp"
#include "../Entities/weightValues.hpp"
#include "MenuGameState.hpp"
#include "gameState.hpp"

PlayAstroGameState::PlayAstroGameState(Engine& engine) : GameState() {
    std::cout << "Play Astro State" << std::endl;
    addEntity(std::make_unique<FpsCounter>(sf::Vector2f(10.f, 10.f)));
    addEntity(std::make_unique<WeightValues>(sf::Vector2f(5.f, 20.f)));
    addEntity(std::make_unique<Ship>(sf::Vector2f(200.f, 200.f), sf::Vector2f(0.f, 0.f)));
    addEntity(std::make_unique<Food>(sf::Vector2f(-100.f, -100.f), sf::Vector2f(1.f, 1.f)));
}

void PlayAstroGameState::handleInput(Engine& engine, sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
            std::cout << "State wechseln..." << std::endl;
            engine.changeState(std::make_unique<MenuGameState>(engine));
        }
    }
    if (event.is<sf::Event::Closed>()) {
        engine.window.close();
    }
}

// void PlayAstroGameState::update(float deltatime, Engine& engine) {
//     m_ship.update(deltatime, engine);
//     m_weightValues.update(m_ship);
//     fpscounter.update(deltatime, engine);
// }

// void PlayAstroGameState::draw(sf::RenderWindow& window) {
//     m_ship.draw(window);
//     fpscounter.draw(window);
//     m_weightValues.draw(window);
// }
