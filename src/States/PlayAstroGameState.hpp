#pragma once
#include "../Entities/ship.hpp"
#include "../Entities/weightValues.hpp"
#include "../engine.hpp"
#include "gameState.hpp"

class PlayAstroGameState : public GameState {
public:
    PlayAstroGameState(Engine& engine);

    void update(float deltatime, Engine& engine) override;
    void draw(sf::RenderWindow& window) override;
    void handleInput(Engine& engine, sf::Event& event) override;

private:
    Ship m_ship;
    WeightValues m_weightValues;
    FpsCounter fpscounter;
};
