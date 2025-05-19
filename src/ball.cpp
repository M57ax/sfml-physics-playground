#include "ball.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

#include "engine.hpp"
// konstruktor
Ball::Ball(float radius, sf::Vector2f vel, sf::Vector2f startPos)
    : Entity(startPos, vel), circle(radius), mass(radius * radius * std::numbers::pi_v<float>) {
    circle.setFillColor(color);
    circle.setPosition(startPos);
}
void Ball::draw(sf::RenderWindow& window) const {
    window.draw(circle);
}

void Ball::update(float deltatime, Engine& engine) {
    update(deltatime, engine.minSpeed, engine.maxSpeed, engine.normalSpeedFactor,
        engine.extraSpeedFactor);
    const auto windowSize = engine.getWindowSize();
    handleWallCollision(windowSize.x, windowSize.y);
}

void Ball::update(float deltatime, float minSpeed, float maxSpeed, float normaldSpeedFactor,
    float extraSpeedFactor) {
    sf::Vector2f pos = circle.getPosition();

    pos.x += velocity.x * deltatime * normaldSpeedFactor * extraSpeedFactor;
    pos.y += velocity.y * deltatime * normaldSpeedFactor * extraSpeedFactor;

    float speed = std::sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    circle.setFillColor(colorBasedOnSpeed(speed, minSpeed, maxSpeed));

    circle.setPosition(pos);
}

void Ball::handleWallCollision(float windowSizeX, float windowSizeY) {
    sf::Vector2f pos = circle.getPosition();
    float radius = circle.getRadius();

    if (pos.x < 0) {
        velocity.x = std::abs(velocity.x);
    } else if (pos.x + radius * 2 > windowSizeX) {
        velocity.x = -std::abs(velocity.x);
    }

    if (pos.y < 0) {
        velocity.y = std::abs(velocity.y);
    } else if (pos.y + radius * 2 > windowSizeY) {
        velocity.y = -std::abs(velocity.y);
    }
}

sf::Color Ball::colorBasedOnSpeed(float speed, float minSpeed, float maxSpeed) {
    float speedInPercent = (speed - minSpeed) / (maxSpeed - minSpeed);
    speedInPercent = std::clamp(speedInPercent, 0.0F, 1.0F);  // range from 0% to 100 %

    int red = 0;
    int green = 0;
    int blue = 0;
    const int maxRGBvalue = 255;

    if (speedInPercent <= 0.25F) {
        blue = maxRGBvalue;
        green = ((speedInPercent / 0.25F) * maxRGBvalue);
    } else if (speedInPercent <= 0.5F) {
        blue = ((1.0F - (speedInPercent - 0.25F) / 0.25F) * maxRGBvalue);
        green = maxRGBvalue;
    } else if (speedInPercent <= 0.75F) {
        red = (((speedInPercent - 0.50F) / 0.25F) * maxRGBvalue);
        green = maxRGBvalue;
    } else if (speedInPercent <= 1.0F) {
        green = ((1.0F - (speedInPercent - 0.75F) / 0.25F) * maxRGBvalue);
        red = maxRGBvalue;
    }
    return (sf::Color(red, green, blue));
}

sf::Vector2f Ball::calcVelocity(const sf::Vector2f velocityA, const sf::Vector2f velocityB,
    const sf::Vector2f posA, const sf::Vector2f posB, float MassA, float MassB) {
    return velocityA -
        ((2 * MassB) / (MassA + MassB)) * (velocityA - velocityB).dot(posA - posB) /
        (posA - posB).lengthSquared() * (posA - posB);
}

sf::Vector2f Ball::getBallCenter(const Ball& ball) {
    return ball.circle.getPosition() +
        sf::Vector2f(ball.circle.getRadius(), ball.circle.getRadius());
}

float Ball::getRadius(const Ball& ball) {
    return ball.circle.getRadius();
}
