#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "ball.hpp"
#include "entity.hpp"
#include "particles.hpp"
using EntityList = std::vector<std::unique_ptr<Entity>>;

class Engine {
    std::vector<std::unique_ptr<Entity>> entities;
    sf::Clock clock;
    sf::RenderWindow window;

    bool isGamePaused = false;

    float baseSpeedFactor = 1.0F;
    float tempModifier = 1.0F;

    void handleInput(sf::Event& event);
    bool isCollision(const Ball& a, const Ball& b);
    void createBalls();
    bool handleCollision(Ball& a, Ball& b);
    Ball createRandomBall();
    // void collisionHandle(float deltatime);

public:
    Engine();
    void gameLoop();
    sf::Vector2u getWindowSize() const;
    float normalSpeedFactor = 2.F;
    float extraSpeedFactor = 2.F;
    static constexpr float minSpeed = 5.0F;
    static constexpr float maxSpeed = 15.0F;
};
