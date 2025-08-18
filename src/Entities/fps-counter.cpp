#include "fps-counter.hpp"

#include <cmath>
#include <iostream>

#include "../engine.hpp"

FpsCounter::FpsCounter(sf::Vector2f position)
    : Entity(position, sf::Vector2f(0.f, 0.f)), fpsText(font) {
    if (!font.openFromFile("assets/roboto.ttf")) {
        std::cerr << "Error" << std::endl;
    }
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color(252, 3, 194));
}

void FpsCounter::update(float deltatime, Engine& engine) {
    int fps = static_cast<int>(std::round(1.f / deltatime));
    fpsText.setString("FPS: " + std::to_string(fps));
}

void FpsCounter::draw(sf::RenderWindow& window) const {
    window.draw(fpsText);
}
