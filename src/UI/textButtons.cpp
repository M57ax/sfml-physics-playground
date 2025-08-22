#include "textButtons.hpp"

#include <iostream>

TextButton::TextButton(const std::string& label, sf::Vector2f position, Callback onClick)
    : Entity(position, {0.f, 0.f}), text(font), onClick(onClick) {
    if (!font.openFromFile("assets/roboto.ttf")) {
        std::cerr << "Error loading font\n";
    }

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(normalColor);
    text.setPosition(position);
}

void TextButton::input(const sf::Event& event, Engine& engine) {
    if (const auto* mouseMove = event.getIf<sf::Event::MouseMoved>()) {
        sf::Vector2f mousePos{(float)mouseMove->position.x, (float)mouseMove->position.y};
        isHovering = text.getGlobalBounds().contains(mousePos);
        text.setFillColor(isHovering ? hoverColor : normalColor);
    }

    if (const auto* mouseClick = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseClick->button == sf::Mouse::Button::Left && isHovering) {
            isEditing = !isEditing;
            text.setFillColor(editingColor);
            std::cout << "Button clicked: " << text.getString().toAnsiString() << "\n";
            if (onClick) {
                onClick(engine);
            }
        }
    }
}

void TextButton::update(float, Engine&) {
}

void TextButton::draw(sf::RenderWindow& window) const {
    window.draw(text);
}
