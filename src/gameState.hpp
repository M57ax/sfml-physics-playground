#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Engine;

class GameState {
public:
    GameState(Engine& engine) {
    }

    virtual ~GameState() = default;

    virtual void update(float deltatime, Engine& engine) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleInput(Engine& engine, sf::Event& event) = 0;
};
