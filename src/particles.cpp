#include "particles.hpp"

#include <iostream>

#include "engine.hpp"
Particle::Particle(sf::Vector2f position, sf::Vector2f velo)
    : Entity(position, velo), velocity(velo), lifetime(3.5) {
    square.setSize({2.0f, 2.0f});
    square.setFillColor(sf::Color::White);
    square.setPosition(position);
}

void Particle::draw(sf::RenderWindow& window) const {
    if (lifetime >= 0.0F) {
        window.draw(square);
    }
}

void Particle::update(float deltatime, Engine& engine) {
    square.move(velocity);
    reduceLifetime(deltatime);
}

void Particle::reduceLifetime(float deltatime) {
    lifetime -= deltatime;
}

void Particle::createSpread(sf::Vector2f position, Engine& engine) {
    engine.entities.emplace_back(std::make_unique<Particle>(position, sf::Vector2f(-4.f, 4.f)));
    engine.entities.emplace_back(std::make_unique<Particle>(position, sf::Vector2f(4.f, 4.f)));
    engine.entities.emplace_back(std::make_unique<Particle>(position, sf::Vector2f(-4.f, -4.f)));
    engine.entities.emplace_back(std::make_unique<Particle>(position, sf::Vector2f(4.f, -4.f)));

    std::cout << "Bum" << std::endl;
}
