#include "particles.hpp"

#include <iostream>

Particle::Particle(sf::Vector2f position, sf::Vector2f velo) : velocity(velo), lifetime(lifetime) {
    square.setSize({2.0f, 2.0f});
    square.setFillColor(sf::Color::White);
    square.setPosition(position);

    lifetime = 0.5F;
}

void Particle::draw(sf::RenderWindow& window) {
    if (lifetime >= 0.0F) {
        window.draw(square);
    }
}

void Particle::update(float deltatime) {
    square.move(velocity);
    reduceLifetime(deltatime);
}

void Particle::reduceLifetime(float deltatime) {
    lifetime -= deltatime;
}
