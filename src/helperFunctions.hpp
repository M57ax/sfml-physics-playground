#pragma once

#include "ball.hpp"
#include "engine.hpp"
#include "entity.hpp"

extern int numberOfBalls;
extern int numberOfParticles;
class Engine;
// using EntityList = std::vector<std::unique_ptr<Entity>>;

void createBalls(Engine& engine);
// void createTestBalls();
void createRandomParticle(Engine& engine, sf::Vector2f position);
bool handleCollision(Ball& a, Ball& b);
void collisionHandle(Engine& engine, float deltatime);
bool isCollision(const Ball& a, const Ball& b);
Ball createRandomBall();
void handleWallCollision(Ball& ball, float windowSizeX, float windowSizeY);

// calc Functions
float calcSpeedValue(float speed, float minSpeed, float maxSpeed);
sf::Color colorBasedOnSpeed(float speedPercentage);
sf::Vector2f calcVelocity(const sf::Vector2f velocityA, const sf::Vector2f velocityB,
    const sf::Vector2f posA, const sf::Vector2f posB, float MassA, float MassB);
