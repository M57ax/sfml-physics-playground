#include "ship.hpp"

#include <cmath>
#include <iostream>

#include "../engine.hpp"
#include "../helperFunctions.hpp"

Ship::Ship(sf::Vector2f startPos, sf::Vector2f initialVelocity)
    : Entity(startPos, initialVelocity) {
    playerShip.setRadius(20.f);
    playerShip.setPointCount(3);
    playerShip.setFillColor(sf::Color::White);

    auto bounds = playerShip.getLocalBounds();
    playerShip.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    playerShip.setPosition(startPos);
    // playerShip.setRotation(sf::degrees(-90.f));
    std::cout << "Schiff DA" << std::endl;
}

void Ship::input(const sf::Event& event, Engine& engine) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
            playerShip.rotate(sf::degrees(-8.f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
            playerShip.rotate(sf::degrees(8.f));
        }

        float rad = playerShip.getRotation().asRadians() - sf::degrees(90.f).asRadians();
        sf::Vector2f moveForward{std::cos(rad), std::sin(rad)};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
            velocity += moveForward * m_shipSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Tab)) {
            velocity += moveForward * m_shipBoost;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
            velocity -= moveForward * m_shipSpeed;
        }
    }
}

void Ship::update(float deltatime, Engine& engine) {
    sf::Vector2f pos = playerShip.getPosition();
    const auto windowSize = engine.getWindowSize();
    float resistance = 0.98f;
    velocity *= resistance;
    playerShip.move(velocity * deltatime);
    handleWallCollision(playerShip, velocity, windowSize.x, windowSize.y);

    for (auto& component : components) {
        component->update(deltatime, *this, engine);
    }
}

void Ship::draw(sf::RenderWindow& window) const {
    window.draw(playerShip);
}
