#include "ball.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

#include "../engine.hpp"
#include "../helperFunctions.hpp"

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
                    createRandomParticle(engine, center);
                }
            } else {
            }
        }
        if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
            if (distance <= circle.getRadius()) {
                addComponent(
                    std::make_unique<FunctionComponent>([](float, Entity& entity, Engine&) {
                        entity.velocity *= 1.001f;
                    }));
            }
        }
    }
}

void Ball::update(float deltatime, Engine& engine) {
    update(deltatime, engine.minSpeed, engine.maxSpeed, engine.keyInputSpeed);
    const auto windowSize = engine.getWindowSize();
    handleWallCollision(*this, windowSize.x, windowSize.y);
    for (auto& component : components) {
        component->update(deltatime, *this, engine);
    }
}

void Ball::update(float deltatime, float minSpeed, float maxSpeed, float keyInputSpeed) {
    sf::Vector2f pos = circle.getPosition();
    pos.x += velocity.x * deltatime * keyInputSpeed;
    pos.y += velocity.y * deltatime * keyInputSpeed;

    float speed = std::sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    float speedPercentage = (calcSpeedValue(speed, minSpeed, maxSpeed));
    circle.setFillColor(colorBasedOnSpeed(speedPercentage));

    circle.setPosition(pos);
}

sf::Vector2f Ball::getBallCenter(const Ball& ball) {
    return ball.circle.getPosition() +
        sf::Vector2f(ball.circle.getRadius(), ball.circle.getRadius());
}

float Ball::getRadius(const Ball& ball) {
    return ball.circle.getRadius();
}
