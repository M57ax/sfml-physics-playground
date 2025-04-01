#include "particles.hpp"

Particle::Particle(sf::Vector2f position) {
    square.setSize({2.0f, 2.0f});
    square.setFillColor(sf::Color::White);
    square.setPosition(position);
};

void Particle::draw(sf::RenderWindow& window) {
    window.draw(square);
}

// void Particle::update(float deltatime) {
//     square.move(velocity * deltatime);
// };
