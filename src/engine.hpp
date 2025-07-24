#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include <functional>

#include "ball.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "fps-counter.hpp"
#include "helperFunctions.hpp"
#include "particles.hpp"

using EntityList = std::vector<std::unique_ptr<Entity>>;
class Engine {
    sf::Clock clock;
    sf::RenderWindow window;

    bool isGamePaused = false;
    float deltatime = 0.0f;
    float baseSpeedFactor = 1.0F;  //
    float tempModifier = 1.0F;     //

    void handleInput(const sf::Event& event);

    void removeDeadEntities();
    void createInputHandlers();

public:
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> newEntities;
    Engine();
    void gameLoop();
    sf::Vector2u getWindowSize() const;
    std::unordered_map<std::string, std::function<void(const sf::Event&, Engine&)>> inputHandler;
    void setTempModifier(float modifier) {
        tempModifier = modifier;
    }

    bool setPaused(bool isPaused) {
        isGamePaused = isPaused;
        return isGamePaused;
    }

    bool isPaused() const {
        return isGamePaused;
    }

    float getBaseSpeedFactor() const {
        return baseSpeedFactor;
    }

    void setBaseSpeedFactor(float baseModifier) {
        baseSpeedFactor = baseModifier;
    }

    float getDeltatime() const {
        return deltatime;
    }

    float keyInputSpeed{};
    float extraSpeedFactor = 2.F;
    float minSpeed = 5.0F;
    float maxSpeed = 15.0F;
};
