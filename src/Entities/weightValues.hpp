#pragma once

#include <SFML/Graphics.hpp>

#include "ship.hpp"

class WeightValues {
public:
    WeightValues(sf::Vector2f position);

    void update(const Ship& ship);
    void draw(sf::RenderWindow& window) const;

private:
    sf::Font font;
    sf::Text currentValue;
    sf::Text targetValue;
};
