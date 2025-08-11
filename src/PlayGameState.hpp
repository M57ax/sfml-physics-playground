#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "engine.hpp"
#include "gameState.hpp"

class PlayGameState : public GameState {
public:
    PlayGameState(Engine& engine);
    virtual void update(float deltatime, Engine& engine) override;
    virtual void draw(sf::RenderWindow& window) override;
    virtual void handleInput(Engine& engine, sf::Event& event) override;
};
