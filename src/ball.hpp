#pragma once

#include <SFML/Graphics.hpp>

#include "entity.hpp"

class Ball : public Entity {
public:
    Ball(float radius, sf::Vector2f vel, sf::Vector2f startPos);
    Ball(const Ball&) = default;
    void draw(sf::RenderWindow& window) const override;
    void update(float deltatime, Engine& engine) override;
    void update(float deltatime, float minSpeed, float maxSpeed, float normalSpeedFactor,
        float extraSpeedFactor);
    void handleWallCollision(float windowSizeX, float windowSizeY);
    static sf::Vector2f getBallCenter(const Ball& ball);
    static float getRadius(const Ball& ball);
    static sf::Vector2f calcVelocity(const sf::Vector2f velocityA, const sf::Vector2f velocityB,
        const sf::Vector2f posA, const sf::Vector2f posB, float MassA, float MassB);

    static sf::Color colorBasedOnSpeed(float speed, float minSpeed, float maxSpeed);

    sf::CircleShape circle;

    sf::Color color;
    float mass = 1;

private:
    bool isCollision(const Ball& a, const Ball& b);
};
