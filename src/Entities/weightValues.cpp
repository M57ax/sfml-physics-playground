#include "weightValues.hpp"

#include <iostream>

WeightValues::WeightValues(sf::Vector2f position) : currentValue(font), targetValue(font) {
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

void WeightValues::update(const Ship& ship) {
    float currentWeight = ship.shipWeigth;
    float targetWeight = ship.targetWeigth;
    currentValue.setString("Current: " + std::to_string(currentWeight));
    targetValue.setString("Target: " + std::to_string(targetWeight));
}

void WeightValues::draw(sf::RenderWindow& window) const {
    window.draw(currentValue);
    window.draw(targetValue);
}
