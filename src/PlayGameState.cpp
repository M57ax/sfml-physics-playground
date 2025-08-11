#include "PlayGameState.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "ball.hpp"
#include "engine.hpp"
#include "fps-counter.hpp"
#include "gameState.hpp"

PlayGameState::PlayGameState(Engine& engine) : GameState(engine) {
    std::cout << "Play State" << std::endl;
    createBalls(engine);
}

void PlayGameState::handleInput(Engine& engine, sf::Event& event) {
}

void PlayGameState::update(float deltatime, Engine& engine) {
}

void PlayGameState::draw(sf::RenderWindow& window) {
}
