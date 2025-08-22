#pragma once

#include <SFML/System/Vector2.hpp>
#include "../entity.hpp"

class Food : public Entity {
public:
    Food(sf::Vector2f position, sf::Vector2f velo);

    void update(float deltatime, Engine& engine) override;
    void draw(sf::RenderWindow& window) const override;
    static sf::Vector2f getCenterFood(const sf::RectangleShape& foodShape);
    sf::FloatRect getBounds() const {
        return foodShape.getGlobalBounds();
    }

    const sf::Shape& getShape() const {
        return foodShape;
    }

private:
    sf::RectangleShape foodShape;
};
