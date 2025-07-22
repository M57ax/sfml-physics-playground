#include "ball.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

#include "engine.hpp"

Ball::Ball(float radius, sf::Vector2f vel, sf::Vector2f startPos)
    : Entity(startPos, vel), circle(radius), mass(radius * radius * std::numbers::pi_v<float>) {
    circle.setFillColor(color);
    circle.setPosition(startPos);
}
void Ball::draw(sf::RenderWindow& window) const {
    window.draw(circle);
}

void Ball::input(const sf::Event& event, Engine& engine) {
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        float mouseX = mouseButtonPressed->position.x;
        float mouseY = mouseButtonPressed->position.y;
        sf::Vector2f center = getBallCenter(*this);
        sf::Vector2f mouse(mouseX, mouseY);
        sf::Vector2f dist = mouse - center;
        float distance = dist.length();
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            if (distance <= circle.getRadius()) {
                std::cout << "In den Ball geklickt " << std::endl;
                addComponent(std::make_unique<PoisonPill>(5.f));
                addComponent(
                    std::make_unique<FunctionComponent>([](float, Entity& entity, Engine&) {
                        entity.velocity *= 0.99f;
                    }));
                for (int i = 0; i < 10; i++) {
                    engine.createRandomParticle(center);
                }
            }

            else {
                // std::cout << "__N__Nicht im Ball" << std::endl;
            }
        }
        if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
            std::cout << "rechts Klick" << std::endl;
        }
    }
}

void Ball::update(float deltatime, Engine& engine) {
    update(deltatime, engine.minSpeed, engine.maxSpeed, engine.keyInputSpeed);
    const auto windowSize = engine.getWindowSize();
    handleWallCollision(windowSize.x, windowSize.y);
    for (auto& component : components) {
        component->update(deltatime, *this, engine);
    }
}

void Ball::update(float deltatime, float minSpeed, float maxSpeed, float keyInputSpeed) {
    sf::Vector2f pos = circle.getPosition();
    pos.x += velocity.x * deltatime * keyInputSpeed;
    pos.y += velocity.y * deltatime * keyInputSpeed;

    float speed = std::sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    float speedPercentage = (calcSpeedvalue(speed, minSpeed, maxSpeed));
    circle.setFillColor(colorBasedOnSpeed(speedPercentage));

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

float Ball::calcSpeedvalue(float speed, float minSpeed, float maxSpeed) {
    return std::clamp((speed - minSpeed) / (maxSpeed - minSpeed), 0.0f, 1.0f);
}

sf::Color Ball::colorBasedOnSpeed(float speedPercentage) {
    int red = 0;
    int green = 0;
    int blue = 0;
    const int maxRGBvalue = 255;

    if (speedPercentage <= 0.25F) {
        blue = maxRGBvalue;
        green = ((speedPercentage / 0.25F) * maxRGBvalue);
    } else if (speedPercentage <= 0.5F) {
        blue = ((1.0F - (speedPercentage - 0.25F) / 0.25F) * maxRGBvalue);
        green = maxRGBvalue;
    } else if (speedPercentage <= 0.75F) {
        red = (((speedPercentage - 0.50F) / 0.25F) * maxRGBvalue);
        green = maxRGBvalue;
    } else if (speedPercentage <= 1.0F) {
        green = ((1.0F - (speedPercentage - 0.75F) / 0.25F) * maxRGBvalue);
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
bool Ball::containsPoint(sf::Vector2f point) const {
    return circle.getGlobalBounds().contains(point);
}
