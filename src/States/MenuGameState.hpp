#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <memory>

#include "../engine.hpp"
#include "gameState.hpp"

class MenuGameState : public GameState {
public:
    MenuGameState(Engine& engine);
    // void update(float deltatime, Engine& engine) override;
    // void draw(sf::RenderWindow& window) override;
    void handleInput(Engine& engine, sf::Event& event) override;

private:
};
