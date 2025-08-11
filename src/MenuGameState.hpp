#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <memory>

#include "engine.hpp"
#include "gameState.hpp"

class MenuGameState : public GameState {
public:
    MenuGameState(Engine& engine);
    virtual void update(float deltatime, Engine& engine) override;
    virtual void draw(sf::RenderWindow& window) override;
    virtual void handleInput(Engine& engine, sf::Event& event) override;

private:
    sf::CircleShape circle;
};
