#pragma once

#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball(float radius, sf::Vector2f vel, sf::Vector2f startPos);

    void update(float windowSizeX, float windowSizeY, float deltatime, float maxBallSpeed,
        float slowMotion, float turboMotion, float minSpeed, float maxSpeed);

    static sf::Vector2f getBallCenter(const Ball& ball);

    static sf::Vector2f calcVelocity(const sf::Vector2f velocityA, const sf::Vector2f velocityB,
        const sf::Vector2f posA, const sf::Vector2f posB, float MassA, float MassB);

    static sf::Color colorBasedOnSpeed(float speed, float minSpeed, float maxSpeed);

    sf::CircleShape circle;
    sf::Vector2f velocity;
    sf::Color color;
    float mass;

private:
    bool isCollision(const Ball& a, const Ball& b);
};
