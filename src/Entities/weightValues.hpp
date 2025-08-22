#pragma once

#include <SFML/Graphics.hpp>

#include "../entity.hpp"
#include "ship.hpp"

class WeightValues : public Entity {
public:
    WeightValues(sf::Vector2f position);

    void update(float deltatime, Engine& engine);
    void draw(sf::RenderWindow& window) const;

private:
    sf::Font font;
    sf::Text currentValue;
    sf::Text targetValue;
};
