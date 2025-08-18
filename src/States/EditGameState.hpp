#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

#include "../UI/textButtons.hpp"
#include "../engine.hpp"
#include "gameState.hpp"

class EditGameState : public GameState {
public:
    EditGameState(Engine& engine);
    void update(float deltatime, Engine& engine) override;
    void draw(sf::RenderWindow& window) override;
    void handleInput(Engine& engine, sf::Event& event) override;

private:
    sf::Font font;
    sf::Text editMenu;
    sf::Text number;
    sf::Text mainMenu;
    TextButton numberParticlesText;
    sf::Text numberParticles;
    TextButton numberBallsText;
};
