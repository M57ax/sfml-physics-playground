#include "weightValues.hpp"

#include <cmath>
#include <iostream>

WeightValues::WeightValues(sf::Vector2f position)
    : Entity(position, sf::Vector2f(0.f, 0.f)), currentValue(font), targetValue(font) {
    if (!font.openFromFile("assets/roboto.ttf")) {
        std::cerr << "Error: Font not found\n";
    }

    currentValue.setFont(font);
    currentValue.setCharacterSize(15);
    currentValue.setFillColor(sf::Color::White);
    currentValue.setPosition(position);

    targetValue.setFont(font);
    targetValue.setCharacterSize(15);
    targetValue.setFillColor(sf::Color::White);
    targetValue.setPosition({position.x, position.y + 25.f});
}

void WeightValues::update(float deltatime, Engine& engine) {
    // float currentWeight = ship.shipWeigth;
    // float targetWeight = ship.targetWeigth;
    currentValue.setString("Current: ");
    targetValue.setString("Target: ");
}

void WeightValues::draw(sf::RenderWindow& window) const {
    window.draw(currentValue);
    window.draw(targetValue);
}
