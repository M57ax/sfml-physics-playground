#pragma once

#include "Entities/ball.hpp"
#include "Entities/ship.hpp"
#include "States/gameState.hpp"
#include "engine.hpp"
#include "entity.hpp"

extern int numberOfBalls;
extern int numberOfParticles;
class Engine;
// using EntityList = std::vector<std::unique_ptr<Entity>>;

// void createShip(Engine& engine);
void createBalls(Engine& engine);
// void createTestBalls();
void createRandomParticle(Engine& engine, sf::Vector2f position);
Ship shipSettings();
bool handleCollision(Ball& a, Ball& b);
void collisionHandle(Engine& engine, float deltatime);
bool checkCollisionFood(const sf::Shape& a, const sf::Shape& b);
void collisionShipFood(Engine& engine, float deltatime);
bool isCollision(const Ball& a, const Ball& b);
Ball createRandomBall();

Ship createRandomStartPos();
void handleWallCollision(
    sf::Shape& shape, sf::Vector2f& velocity, float windowSizeX, float windowSizeY);

// calc Functions
float calcSpeedValue(float speed, float minSpeed, float maxSpeed);
sf::Color colorBasedOnSpeed(float speedPercentage);
sf::Vector2f calcVelocity(const sf::Vector2f velocityA, const sf::Vector2f velocityB,
    const sf::Vector2f posA, const sf::Vector2f posB, float MassA, float MassB);
