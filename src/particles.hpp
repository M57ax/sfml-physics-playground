#pragma once

#include <SFML/Graphics.hpp>

#include "entity.hpp"

class Particle : public Entity {
public:
    Particle(sf::Vector2f position, sf::Vector2f velo);

    void update(float deltatime, Engine& engine) override;
    void draw(sf::RenderWindow& window) const override;
    // static constexpr float particleLifetime = 0.5;
    sf::RectangleShape square;
    // float lifetime = particleLifetime;
    // bool isDead() const override;

private:
    void reduceLifetime(float deltatime);
};
