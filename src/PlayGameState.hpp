#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "engine.hpp"
#include "gameState.hpp"

class PlayGameState : public GameState {
public:
    PlayGameState(Engine& engine);
    void update(float deltatime, Engine& engine) override;
    void draw(sf::RenderWindow& window) override;
    void handleInput(Engine& engine, sf::Event& event) override;

private:
    FpsCounter fpscounter;
};
