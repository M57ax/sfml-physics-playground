#pragma once
#include <SFML/Graphics.hpp>

#include "../entity.hpp"

class FpsCounter : public Entity {
public:
    FpsCounter(sf::Vector2f position);

    void update(float deltatime, Engine& engine) override;
    void draw(sf::RenderWindow& window) const override;

private:
    sf::Font font;
    sf::Text fpsText;
};
