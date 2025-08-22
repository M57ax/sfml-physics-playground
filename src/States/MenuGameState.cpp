#include "MenuGameState.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "../Entities/ship.hpp"
#include "../UI/textButtons.hpp"
#include "../engine.hpp"
#include "EditGameState.hpp"
#include "PlayAstroGameState.hpp"
#include "PlayGameState.hpp"
#include "gameState.hpp"

MenuGameState::MenuGameState(Engine& engine) : GameState() {
    std::cout << "Menu State Constructor" << std::endl;

    // engine.addEntity(std::make_unique<Ship>(sf::Vector2f(200.f, 200.f), sf::Vector2f(0.f, 0.f)));
    // engine.addEntity(std::make_unique<FpsCounter>(sf::Vector2f(10.f, 10.f)));
    addEntity(
        std::make_unique<TextButton>("Game Menu(soll nicht hovern)", sf::Vector2f(630.f, 150.f)));

    addEntity(std::make_unique<TextButton>(
        "Play Astro Atoma", sf::Vector2f(635.f, 510.f), [](Engine& eng) {
            std::cout << "Start Astro...\n";
            eng.changeState(std::make_unique<PlayAstroGameState>(eng));
        }));
    addEntity(std::make_unique<TextButton>(
        "Play Bouncing Balls", sf::Vector2f(635.f, 250.f), [](Engine& eng) {
            std::cout << "Start Bouncing Balls...\n";
            // createBalls(eng);
            eng.changeState(std::make_unique<PlayGameState>(eng));
        }));
    addEntity(std::make_unique<TextButton>(
        "Edit Bouncing Balls", sf::Vector2f(635.f, 310.f), [](Engine& eng) {
            std::cout << "Edit Bouncing Balls...\n";
            eng.changeState(std::make_unique<EditGameState>(eng));
        }));
}

void MenuGameState::handleInput(Engine& engine, sf::Event& event) {
    // if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
    //     if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
    //         sf::Vector2f mousePos(static_cast<float>(mouseButtonPressed->position.x),
    //             static_cast<float>(mouseButtonPressed->position.y));
    //         if (playBBText.getGlobalBounds().contains(mousePos)) {
    //             std::cout << "Start Bouncing Balls..." << std::endl;
    //             engine.popState();
    //             engine.pushState(std::make_unique<PlayGameState>(engine));
    //         } else if (editText.getGlobalBounds().contains(mousePos)) {
    //             std::cout << "Edit Button geklickt" << std::endl;
    //             engine.popState();
    //             engine.pushState(std::make_unique<EditGameState>(engine));
    //         } else if (playAstroAtoma.getGlobalBounds().contains(mousePos)) {
    //             std::cout << "Start Astro Atoma ...." << std::endl;
    //             engine.popState();
    //             engine.pushState(std::make_unique<PlayAstroGameState>(engine));
    //         }
    //     }
    // }
    // if (event.is<sf::Event::Closed>()) {
    //     engine.window.close();
    // }
}
