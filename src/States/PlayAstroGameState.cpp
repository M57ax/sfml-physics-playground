#include "PlayAstroGameState.hpp"

#include <iostream>

#include "../Entities/fps-counter.hpp"
#include "MenuGameState.hpp"
#include "gameState.hpp"

PlayAstroGameState::PlayAstroGameState(Engine& engine)
    : m_ship({1300.f, 100.f}, {0.f, 0.f}),
      m_weightValues({0.f, 30.f}),
      fpscounter(sf::Vector2f(10.f, 10.f)),
      GameState(engine) {
    std::cout << "Asto Boy" << std::endl;
}

void PlayAstroGameState::handleInput(Engine& engine, sf::Event& event) {
    m_ship.input(event, engine);
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

void PlayAstroGameState::update(float deltatime, Engine& engine) {
    m_ship.update(deltatime, engine);
    m_weightValues.update(m_ship);
    fpscounter.update(deltatime, engine);
}

void PlayAstroGameState::draw(sf::RenderWindow& window) {
    m_ship.draw(window);
    fpscounter.draw(window);
    m_weightValues.draw(window);
}
