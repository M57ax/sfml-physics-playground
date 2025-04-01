#pragma once

#include <SFML/Graphics.hpp>

class Particle {
public:
    Particle(sf::Vector2f position, sf::Vector2f velo);

    void update(float deltatime);
    void draw(sf::RenderWindow& window);

    sf::RectangleShape square;
    sf::Vector2f velocity;

private:
};
