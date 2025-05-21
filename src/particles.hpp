#pragma once

#include <SFML/Graphics.hpp>

#include "entity.hpp"

class Particle : public Entity {
public:
    Particle(sf::Vector2f position, sf::Vector2f velo);

    void update(float deltatime, Engine& engine) override;
    void draw(sf::RenderWindow& window) const override;

    sf::RectangleShape square;
    sf::Vector2f velocity;
    float lifetime;
    bool isDead() const override;

private:
    void reduceLifetime(float deltatime);
};
