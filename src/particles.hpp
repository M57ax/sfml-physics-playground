#pragma once

#include <SFML/Graphics.hpp>

#include "entity.hpp"

class Particle : public Entity {
public:
    Particle(sf::Vector2f position, sf::Vector2f velo);
    static std::vector<std::unique_ptr<Particle>> createSpread(sf::Vector2f position);

    void update(float deltatime, Engine& engine) override;
    void draw(sf::RenderWindow& window) const override;
    static void createSpread(sf::Vector2f position, Engine& engine);
    // bool particleAlive();
    sf::RectangleShape square;
    sf::Vector2f velocity;
    float lifetime = 0.5F;
    float getLifetime() const {
        return lifetime;
    }  // warum hier error ohne ";"?

private:
    void reduceLifetime(float deltatime);
};
