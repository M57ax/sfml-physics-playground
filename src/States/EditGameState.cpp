#include "EditGameState.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "../UI/textButtons.hpp"
#include "../engine.hpp"
#include "../helperFunctions.hpp"
#include "MenuGameState.hpp"
#include "gameState.hpp"

bool hoverNumber = false;
bool hoverParticles = false;

enum class ActiveField { None, Number, Particles };
ActiveField active = ActiveField::None;

EditGameState::EditGameState(Engine& engine)
    : GameState(),
      editMenu(font),
      number(font),
      mainMenu(font),
      numberParticlesText("Number of Particles per Collision", {20.0f, 250.0f}),
      numberParticles(font),
      numberBallsText("Text for how many balls", {20.0f, 150.0f}) {
    std::cout << "Edit State" << std::endl;
    if (!font.openFromFile("assets/roboto.ttf")) {
        std::cerr << "Error" << std::endl;
    }

    addEntity(std::make_unique<TextButton>("EDIT MENU", sf::Vector2f(630.f, 150.f)));

    editMenu.setFont(font);
    editMenu.setFillColor(sf::Color::White);
    editMenu.setCharacterSize(50);
    editMenu.setPosition(sf::Vector2f(670.0f, 50.0f));
    editMenu.setString("Edit Menu");

    number.setFont(font);
    number.setFillColor(sf::Color::White);
    number.setCharacterSize(30);
    number.setPosition(sf::Vector2f(670.0f, 150.0f));

    mainMenu.setFont(font);
    mainMenu.setFillColor(sf::Color::White);
    mainMenu.setCharacterSize(30);
    mainMenu.setPosition(sf::Vector2f(670.0f, 550.0f));

    // numberParticlesText.setFont(font);
    // numberParticlesText.setFillColor(sf::Color::White);
    // numberParticlesText.setCharacterSize(30);
    // numberParticlesText.setPosition(sf::Vector2f(20.0f, 250.0f));
    // numberParticlesText.setString("Number of Particles per Collision: ");

    numberParticles.setFont(font);
    numberParticles.setFillColor(sf::Color::White);
    numberParticles.setCharacterSize(30);
    numberParticles.setPosition(sf::Vector2f(670.0f, 250.0f));
}

// void EditGameState::update(float deltatime, Engine& engine) {
//     number.setString(std::to_string(numberOfBalls));
//     numberParticles.setString(std::to_string(numberOfParticles));
//     mainMenu.setString("Back to Menu");
// }

void EditGameState::handleInput(Engine& engine, sf::Event& event) {
    if (const auto* mouseMove = event.getIf<sf::Event::MouseMoved>()) {
        sf::Vector2f mouse{(float)mouseMove->position.x, (float)mouseMove->position.y};
        hoverNumber = number.getGlobalBounds().contains(mouse);
        hoverParticles = numberParticles.getGlobalBounds().contains(mouse);
    }

    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButton->button == sf::Mouse::Button::Left) {
            sf::Vector2f mouse{(float)mouseButton->position.x, (float)mouseButton->position.y};

            if (number.getGlobalBounds().contains(mouse)) {
                active = ActiveField::Number;
            } else if (numberParticles.getGlobalBounds().contains(mouse)) {
                active = ActiveField::Particles;
            } else if (mainMenu.getGlobalBounds().contains(mouse)) {
                std::cout << "Back to Main Menu Button geklickt\n";

                engine.changeState(std::make_unique<MenuGameState>(engine));
            } else {
                active = ActiveField::None;
            }
        }
    }

    if (const auto* keyp = event.getIf<sf::Event::KeyPressed>()) {
        if (active == ActiveField::Number) {
            if (keyp->scancode == sf::Keyboard::Scancode::Right) ++numberOfBalls;
            if (keyp->scancode == sf::Keyboard::Scancode::Left) --numberOfBalls;
        } else if (active == ActiveField::Particles) {
            if (keyp->scancode == sf::Keyboard::Scancode::Right) ++numberOfParticles;
            if (keyp->scancode == sf::Keyboard::Scancode::Left) --numberOfParticles;
        }
    }

    if (hoverNumber || active == ActiveField::Number) {
        number.setFillColor(sf::Color::Yellow);
    } else {
        number.setFillColor(sf::Color::White);
    }

    if (hoverParticles || active == ActiveField::Particles) {
        numberParticles.setFillColor(sf::Color::Yellow);
    } else {
        numberParticles.setFillColor(sf::Color::White);
    }
}

// void EditGameState::draw(sf::RenderWindow& window) {
//     window.draw(editMenu);
//     window.draw(number);
//     window.draw(mainMenu);
//     numberParticlesText.draw(window);
//     window.draw(numberParticles);
//     numberBallsText.draw(window);
// }
