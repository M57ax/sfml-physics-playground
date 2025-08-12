#include "EditGameState.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "MenuGameState.hpp"
#include "engine.hpp"
#include "gameState.hpp"
#include "helperFunctions.hpp"

EditGameState::EditGameState(Engine& engine)
    : GameState(engine),
      numberBallsText(font),
      editMenu(font),
      number(font),
      mainMenu(font),
      numberParticlesText(font),
      numberParticles(font) {
    std::cout << "Edit State" << std::endl;
    if (!font.openFromFile("assets/roboto.ttf")) {
        std::cerr << "Error" << std::endl;
    }

    editMenu.setFont(font);
    editMenu.setFillColor(sf::Color::White);
    editMenu.setCharacterSize(50);
    editMenu.setPosition(sf::Vector2f(670.0f, 50.0f));
    editMenu.setString("Edit Menu");

    numberBallsText.setFont(font);
    numberBallsText.setFillColor(sf::Color::White);
    numberBallsText.setCharacterSize(30);
    numberBallsText.setPosition(sf::Vector2f(20.0f, 150.0f));
    numberBallsText.setString("Number of Balls: ");

    number.setFont(font);
    number.setFillColor(sf::Color::White);
    number.setCharacterSize(30);
    number.setPosition(sf::Vector2f(670.0f, 150.0f));

    mainMenu.setFont(font);
    mainMenu.setFillColor(sf::Color::White);
    mainMenu.setCharacterSize(30);
    mainMenu.setPosition(sf::Vector2f(670.0f, 550.0f));

    numberParticlesText.setFont(font);
    numberParticlesText.setFillColor(sf::Color::White);
    numberParticlesText.setCharacterSize(30);
    numberParticlesText.setPosition(sf::Vector2f(20.0f, 250.0f));
    numberParticlesText.setString("Number of Particles per Collision: ");

    numberParticles.setFont(font);
    numberParticles.setFillColor(sf::Color::White);
    numberParticles.setCharacterSize(30);
    numberParticles.setPosition(sf::Vector2f(670.0f, 250.0f));
}

void EditGameState::update(float deltatime, Engine& engine) {
    number.setString(std::to_string(numberOfBalls));
    numberParticles.setString(std::to_string(numberOfParticles));
    mainMenu.setString("Back to Menu");
}

void EditGameState::handleInput(Engine& engine, sf::Event& event) {
    if (const auto* mouseButtonHover = event.getIf<sf::Event::MouseMoved>()) {
        sf::Vector2f mousePosRN(static_cast<float>(mouseButtonHover->position.x),
            static_cast<float>(mouseButtonHover->position.y));
        if (number.getGlobalBounds().contains(mousePosRN)) {
            isHovering = true;
        } else {
            isHovering = false;
        }
    }

    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos(static_cast<float>(mouseButtonPressed->position.x),
                static_cast<float>(mouseButtonPressed->position.y));
            if (number.getGlobalBounds().contains(mousePos)) {
                isEditing = true;
                number.setFillColor(sf::Color::Yellow);
            }
            if (!number.getGlobalBounds().contains(mousePos)) {
                isEditing = false;
                number.setFillColor(sf::Color::White);
            }
        }
    }

    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos(static_cast<float>(mouseButtonPressed->position.x),
                static_cast<float>(mouseButtonPressed->position.y));
            if (mainMenu.getGlobalBounds().contains(mousePos)) {
                std::cout << "Back to Main Menu Button geklickt" << std::endl;
                engine.pushState(std::make_unique<MenuGameState>(engine));
                // engine.popState();
            }
        }
    }

    if (isEditing) {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
                std::cout << "More Balls" << std::endl;
                static_cast<int>(numberOfBalls);
                numberOfBalls++;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Left) {
                std::cout << "Less Balls" << std::endl;
                static_cast<int>(numberOfBalls);
                numberOfBalls--;
            }
        }
    }
    if (isHovering) {
        number.setFillColor(sf::Color::Yellow);
    }
    if (!isHovering && !isEditing) {
        number.setFillColor(sf::Color::White);
    }
}

// Bälle können jetzt im Edit Menü verstellt werden
//  Es müssen noch weniger werden, und dann Partikel einstellen
void EditGameState::draw(sf::RenderWindow& window) {
    window.draw(editMenu);
    window.draw(numberBallsText);
    window.draw(number);
    window.draw(mainMenu);
    window.draw(numberParticlesText);
    window.draw(numberParticles);
}
