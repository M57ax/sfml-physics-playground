#include "MenuGameState.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "../engine.hpp"
#include "EditGameState.hpp"
#include "PlayAstroGameState.hpp"
#include "PlayGameState.hpp"
#include "gameState.hpp"

MenuGameState::MenuGameState(Engine& engine)
    : GameState(engine),
      playBBText(font),
      gameNameText(font),
      editText(font),
      playAstroAtoma(font) {
    std::cout << "Menu State Constructor" << std::endl;
    if (!font.openFromFile("assets/roboto.ttf")) {
        std::cerr << "Error" << std::endl;
    }
    gameNameText.setFont(font);
    gameNameText.setCharacterSize(50);
    gameNameText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    gameNameText.setFillColor(sf::Color::White);
    gameNameText.setPosition(sf::Vector2f(630.0f, 150.f));

    playBBText.setFont(font);
    playBBText.setCharacterSize(30);
    playBBText.setFillColor(sf::Color::White);
    playBBText.setPosition(sf::Vector2f(635.0f, 250.0f));

    editText.setFont(font);
    editText.setCharacterSize(30);
    editText.setFillColor(sf::Color::White);
    editText.setPosition(sf::Vector2f(635.0f, 310.0f));

    playAstroAtoma.setFont(font);
    playAstroAtoma.setCharacterSize(30);
    playAstroAtoma.setFillColor(sf::Color::White);
    playAstroAtoma.setPosition(sf::Vector2f(635.f, 510.0f));
}

void MenuGameState::handleInput(Engine& engine, sf::Event& event) {
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos(static_cast<float>(mouseButtonPressed->position.x),
                static_cast<float>(mouseButtonPressed->position.y));
            if (playBBText.getGlobalBounds().contains(mousePos)) {
                std::cout << "Start Bouncing Balls..." << std::endl;
                engine.popState();
                engine.pushState(std::make_unique<PlayGameState>(engine));
            } else if (editText.getGlobalBounds().contains(mousePos)) {
                std::cout << "Edit Button geklickt" << std::endl;
                engine.popState();
                engine.pushState(std::make_unique<EditGameState>(engine));
            } else if (playAstroAtoma.getGlobalBounds().contains(mousePos)) {
                std::cout << "Start Astro Atoma ...." << std::endl;
                engine.popState();
                engine.pushState(std::make_unique<PlayAstroGameState>(engine));
            }
        }
    }
    if (event.is<sf::Event::Closed>()) {
        engine.window.close();
    }
}

void MenuGameState::update(float deltatime, Engine& engine) {
    gameNameText.setString("Game Menu");
    playBBText.setString("Play Bouncing Balls");
    editText.setString("Edit Bouncing Balls");
    playAstroAtoma.setString("Play Astro-Atoma");
}

void MenuGameState::draw(sf::RenderWindow& window) {
    window.draw(gameNameText);
    window.draw(playBBText);
    window.draw(editText);
    window.draw(playAstroAtoma);
}
