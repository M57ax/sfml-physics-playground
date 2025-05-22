#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include <functional>

#include "ball.hpp"
#include "entity.hpp"
#include "particles.hpp"

using EntityList = std::vector<std::unique_ptr<Entity>>;
class Engine {
    sf::Clock clock;
    sf::RenderWindow window;
    sf::RenderWindow editWindow;

    bool editWindowOpen = false;
    bool isGamePaused = false;

    float baseSpeedFactor = 1.0F;
    float tempModifier = 1.0F;

    void handleInput(const sf::Event& event);
    bool isCollision(const Ball& a, const Ball& b);
    void createBalls();
    bool handleCollision(Ball& a, Ball& b);

    void createRandomParticle(sf::Vector2f position);
    void createParticle(sf::Vector2f position);
    void collisionHandle(float deltatime);
    void removeDeadEntities();
    void createTestBalls();
    void createInputHandlers();

public:
    Ball createRandomBall();
    std::vector<std::unique_ptr<Entity>> entities;
    Engine();
    void gameLoop();
    sf::Vector2u getWindowSize() const;
    std::unordered_map<std::string, std::function<void(const sf::Event&, Engine&)>> inputHandler;
    sf::View viewZoom;
    void setTempModifier(float modifier) {
        tempModifier = modifier;
    }

    float keyInputSpeed{};
    float extraSpeedFactor = 2.F;
    float minSpeed = 5.0F;
    float maxSpeed = 15.0F;
};
