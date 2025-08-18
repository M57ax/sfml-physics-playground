#include "textButtons.hpp"

#include <iostream>

#include "../engine.hpp"

TextButton::TextButton(const std::string& label, sf::Vector2f position) : text(font, label, 30) {
    if (!font.openFromFile("assets/roboto.ttf")) {
        std::cerr << "Error loading font\n";
    }
    text.setFillColor(normalColor);
    text.setPosition(position);

    std::cout << "test text" << std::endl;
}

void TextButton::handleInput(Engine& engine, sf::Event& event) {
}

void TextButton::update(float deltatime, Engine& engine) {
}

void TextButton::draw(sf::RenderWindow& window) {
    window.draw(text);
}
