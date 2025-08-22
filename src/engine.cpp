#include "engine.hpp"

#include <iostream>
#include <random>

#include "Entities/ball.hpp"
#include "Entities/fps-counter.hpp"
#include "Entities/particles.hpp"
#include "States/EditGameState.hpp"
#include "States/MenuGameState.hpp"
#include "States/PlayGameState.hpp"
#include "States/gameState.hpp"
#include "component.hpp"
#include "helperFunctions.hpp"

Engine::Engine() : window(sf::VideoMode({1500, 800}), "Bouncing Balls") {
    constexpr int maxFps = 60;
    window.setFramerateLimit(maxFps);
}

void Engine::handleInput(const sf::Event& event) {
    if (event.is<sf::Event::Closed>()) {
        window.close();
    }
    for (auto& [_, handler] : inputHandler) {
        handler(event, *this);
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
                if (auto* st = engine.currentState()) {
                    st->addEntity(std::move(ball));
                }
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::C) {
                auto newBall = std::make_unique<Ball>(createRandomBall());
                if (auto* st = engine.currentState()) {
                    st->addEntity(std::move(newBall));
                }
            }
        }
    });
    inputHandler.emplace("speedUpAndDown", &speedUpDown);
    inputHandler.emplace("pause", &pauseMode);
}

void Engine::removeDeadEntities() {
    if (auto* st = currentState()) {
        auto& ents = st->getEntities();
        ents.erase(std::remove_if(ents.begin(), ents.end(),
                       [](const std::unique_ptr<Entity>& entity) {
                           return entity->isDead();
                       }),
            ents.end());
    }
}

void Engine::changeState(std::unique_ptr<GameState> state) {
    std::cout << "Change...\n";
    nextState = std::move(state);
}
void Engine::startState(std::unique_ptr<GameState> state) {
    std::cout << "Start...\n";
    current = std::move(state);
}

GameState* Engine::currentState() {
    return current.get();
}

// void Engine::clearAll() {
//     entities.clear();
//     newEntities.clear();
// }

void Engine::gameLoop() {
    createInputHandlers();

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (auto event = window.pollEvent()) {
            handleInput(*event);
            if (auto* state = currentState()) {
                for (auto& e : state->getEntities()) {
                    e->input(*event, *this);
                }
                state->handleInput(*this, *event);
            }
        }

        if (!isGamePaused) {
            if (auto* state = currentState()) {
                collisionHandle(*this, deltatime);
                removeDeadEntities();
                state->pushNewEntities();
                for (auto& e : state->getEntities()) {
                    e->update(dt, *this);
                }
            }
        }

        window.clear();
        if (auto* state = currentState()) {
            for (auto& e : state->getEntities()) {
                e->draw(window);
            }
        }
        if (nextState) {
            current = std::move(nextState);
        }

        window.display();
    }
}

sf::Vector2u Engine::getWindowSize() const {
    return window.getSize();
}
