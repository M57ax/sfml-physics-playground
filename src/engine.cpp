#include "engine.hpp"

#include <iostream>
#include <random>

#include "EditGameState.hpp"
#include "MenuGameState.hpp"
#include "PlayGameState.hpp"
#include "ball.hpp"
#include "component.hpp"
#include "fps-counter.hpp"
#include "helperFunctions.hpp"
#include "particles.hpp"
// Momentan ist der Stand so, dass ich über den MenuState, einfach den Play
// State auf den stack lege aber der darunter liegende state wird nicht
//  gelöscht. Also MenuState anschauen und darum kümmern, dass State ordentlich
//  gelöscht wird.

Engine::Engine() : window(sf::VideoMode({1500, 800}), "Bouncing Balls") {
    constexpr int maxFps = 60;
    window.setFramerateLimit(maxFps);
}

void Engine::handleInput(const sf::Event& event) {
    if (event.is<sf::Event::Closed>()) {
        window.close();
    }
    for (auto& [key, value] : inputHandler) {
        value(event, *this);
    }

    keyInputSpeed = baseSpeedFactor * tempModifier;
}

void slowmoAndTurbo(const sf::Event&, Engine& engine) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
        engine.setTempModifier(50.0F);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        engine.setTempModifier(0.09F);
    } else {
        engine.setTempModifier(10.0F);
    }
}

void speedUpDown(const sf::Event& event, Engine& engine) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::P) {
            engine.setBaseSpeedFactor(std::clamp(engine.getBaseSpeedFactor() + 0.3F, 0.1F, 15.F));
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::M) {
            engine.setBaseSpeedFactor(std::clamp(engine.getBaseSpeedFactor() - 0.3F, 0.1F, 15.F));
        }
    }
}

void pauseMode(const sf::Event& event, Engine& engine) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
            engine.setPaused(!engine.isPaused());
        }
    }
}

void Engine::createInputHandlers() {
    inputHandler.emplace("turbo", &slowmoAndTurbo);
    inputHandler.emplace("plusBall", [](const sf::Event& event, Engine& engine) {
        if (!dynamic_cast<PlayGameState*>(engine.currentState())) return;
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::F) {
                auto ball = std::make_unique<Ball>(createRandomBall());
                ball->addComponent(std::make_unique<PoisonPill>(5.0f));
                engine.entities.emplace_back(std::move(ball));
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::C) {
                auto newBall = std::make_unique<Ball>(createRandomBall());
                engine.entities.emplace_back(std::move(newBall));
            }
        }
    });
    inputHandler.emplace("speedUpAndDown", &speedUpDown);
    inputHandler.emplace("pause", &pauseMode);
}

void Engine::removeDeadEntities() {
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                       [](const std::unique_ptr<Entity>& entity) {
                           return entity->isDead();
                       }),
        entities.end());
}
void Engine::pushState(std::unique_ptr<GameState> state) {
    states.push(std::move(state));
}

void Engine::popState() {
    if (!states.empty()) {
        states.pop();
        std::cout << "State wird GELÖSCHT" << std::endl;
    }
}

void Engine::changeState(std::unique_ptr<GameState> state) {
    if (!states.empty()) {
        popState();
    }
    pushState(std::move(state));
}
GameState* Engine::currentState() {
    if (!states.empty()) {
        return states.top().get();
    }
    return nullptr;
}

void Engine::clearAll() {
    entities.clear();
    newEntities.clear();
}

void Engine::gameLoop() {
    // entities.emplace_back(std::make_unique<FpsCounter>(sf::Vector2f()));
    createInputHandlers();
    sf::Vector2u windowSize = window.getSize();

    while (window.isOpen()) {
        float deltatime = clock.restart().asSeconds();

        while (std::optional event = window.pollEvent()) {
            handleInput(event.value());
            for (auto& entity : entities) {
                entity->input(event.value(), *this);
            }

            if (auto* state = currentState()) {
                state->handleInput(*this, event.value());
            }
        }

        if (auto* state = currentState()) {
            state->update(deltatime, *this);
        }

        if (!isGamePaused) {
            collisionHandle(*this, deltatime);
            for (auto& entity : entities) {
                entity->update(deltatime, *this);
            }
            removeDeadEntities();
        }

        for (auto& entity : newEntities) {
            entities.emplace_back(std::move(entity));
        }
        newEntities.clear();

        window.clear();

        if (auto* state = currentState()) {
            state->draw(window);
        }

        for (auto& entity : entities) {
            entity->draw(window);
        }

        window.display();
    }
}

sf::Vector2u Engine::getWindowSize() const {
    return window.getSize();
}
