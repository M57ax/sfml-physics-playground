#pragma once

#include <SFML/Graphics.hpp>

class Particle {
public:
    Particle(sf::Vector2f position);

    void update(float deltatime);
    void draw(sf::RenderWindow& window);

    sf::RectangleShape square;
    // sf::Vector2f velocity;

private:
};
