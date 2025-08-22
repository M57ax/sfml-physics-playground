#include "food.hpp"
#include <SFML/System/Vector2.hpp>

#include <iostream>

#include "../engine.hpp"

Food::Food(sf::Vector2f position, sf::Vector2f velo) : Entity(position, velo) {
    foodShape.setSize({15.f, 15.f});
    foodShape.setFillColor(sf::Color::Magenta);
    foodShape.setPosition(position);
}

void Food::update(float deltatime, Engine& engine) {
    foodShape.move(velocity);
    for (auto& component : components) {
        component->update(deltatime, *this, engine);
    }
}

void Food::draw(sf::RenderWindow& window) const {
    window.draw(foodShape);
}
