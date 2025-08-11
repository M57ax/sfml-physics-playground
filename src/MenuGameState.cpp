#include "MenuGameState.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "PlayGameState.hpp"
#include "engine.hpp"
#include "gameState.hpp"

MenuGameState::MenuGameState(Engine& engine)
    : GameState(engine), playText(font), gameNameText(font) {
    std::cout << "Menu State Constructor" << std::endl;
    if (!font.openFromFile("assets/roboto.ttf")) {
        std::cerr << "Error" << std::endl;
    }
    playText.setFont(font);
    playText.setCharacterSize(30);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(sf::Vector2f(750.0f, 450.0f));
    gameNameText.setFont(font);
    gameNameText.setCharacterSize(50);
    gameNameText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    gameNameText.setFillColor(sf::Color::White);
    gameNameText.setPosition(sf::Vector2f(630.0f, 250.f));
}

void MenuGameState::handleInput(Engine& engine, sf::Event& event) {
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos(static_cast<float>(mouseButtonPressed->position.x),
                static_cast<float>(mouseButtonPressed->position.y));
            if (playText.getGlobalBounds().contains(mousePos)) {
                std::cout << "Button geklickt" << std::endl;
                engine.popState();
                engine.pushState(std::make_unique<PlayGameState>(engine));
            }
        }
    }
    if (event.is<sf::Event::Closed>()) {
        engine.window.close();
    }
}

void MenuGameState::update(float deltatime, Engine& engine) {
    playText.setString("Play");
    gameNameText.setString("Bouncing Balls");
}

void MenuGameState::draw(sf::RenderWindow& window) {
    window.draw(gameNameText);
    window.draw(playText);
}
