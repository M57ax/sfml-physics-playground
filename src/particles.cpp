#include "particles.hpp"

#include <iostream>

#include "engine.hpp"

Particle::Particle(sf::Vector2f position, sf::Vector2f velo) : Entity(position, velo) {
    square.setSize({2.0f, 2.0f});
    square.setFillColor(sf::Color::White);
    square.setPosition(position);
}

void Particle::draw(sf::RenderWindow& window) const {
    window.draw(square);
}

void Particle::update(float deltatime, Engine& engine) {
    square.move(velocity);
    for (auto& component : components) {
        component->update(deltatime, *this, engine);
    }
}
